
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Animation::Animation(const char* path) {
	this->load(path);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Animation::~Animation() {
	delete this->keyframeNode;
}


/*------------------------------------------------------------------------------
< update pose >
------------------------------------------------------------------------------*/
void Animation::updatePose(std::vector<glm::mat4>& pose, const Node<Bone>* rootNode, float timeInSeconds) {
	timeInSeconds = timeInSeconds - lastStartTimeInSeconds; // animation always starts from the beginning
	float timeInTicks = timeInSeconds * this->ticksPerSecond;
	this->animationTimeInTicks = fmod(timeInTicks, this->duration);

	// animation blending
	this->blendFactor = timeInSeconds / this->blendTimeInSeconds;

	/* for mixamo models */
	this->processPose(pose, this->keyframeNode, rootNode, glm::mat4(1.0));
	/* for unreal engine models */
	// this->processPose(pose, this->keyframeNode->children[0], rootNode->children[0]->children[0], bones, Matrix4::identity(), animationTimeInTicks);
}


/*------------------------------------------------------------------------------
< reset >
restart animation from beginning
------------------------------------------------------------------------------*/
void Animation::reset(float timeInSeconds) {
	this->lastStartTimeInSeconds = timeInSeconds;
}


/*------------------------------------------------------------------------------
< load animation >
loads a model with supported ASSIMP extensions from file and stores the resulting animation keyframes in a node tree.
------------------------------------------------------------------------------*/
void Animation::load(const char* path) {
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* aiscene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights);
	// check for errors
	if(!aiscene || !aiscene->mRootNode) {
		std::cout << "[ERROR] ASSIMP: " << importer.GetErrorString() << std::endl;
		return;
	}

	// copy aiAnimation
	if (aiscene->mNumAnimations == 1) {
		this->duration = aiscene->mAnimations[0]->mDuration;
		this->ticksPerSecond = aiscene->mAnimations[0]->mTicksPerSecond;
	}
	else {
		std::cout << "[ERROR] ASSIMP: wrong number of animations" << std::endl;
		return;
	}

	// process assimp root node recursively
	this->keyframeNode = new Node<Keyframe>(aiscene->mRootNode->mName.data);
	this->processNode(this->keyframeNode, aiscene->mRootNode, aiscene);
}


/*------------------------------------------------------------------------------
< process keyframe node >
check every aiNodeAnim if mNodeName matches keyframeNode name
if match then copy the aiNodeAnim data (mPositionKeys mRotationKeys mScalingKeys) to keyframeNode data
------------------------------------------------------------------------------*/
void Animation::processNode(Node<Keyframe>* keyframeNode, const aiNode* ainode, const aiScene* aiscene) {
	// check every aiNodeAnim if mNodeName matches keyframeNode name
	// if match then copy the aiNodeAnim data (mNumPositionKeys mNumRotationKeys mNumScalingKeys) to keyframeNode data
	for (unsigned int i = 0; i < aiscene->mAnimations[0]->mNumChannels; i++) {
		if (keyframeNode->name == aiscene->mAnimations[0]->mChannels[i]->mNodeName.data) {
			keyframeNode->data = new Keyframe();
			// copy keyframes
			for (unsigned int j = 0; j < aiscene->mAnimations[0]->mChannels[i]->mNumPositionKeys; j++) {
				VectorKey vectorKey;
				vectorKey.time = aiscene->mAnimations[0]->mChannels[i]->mPositionKeys[j].mTime;
				vectorKey.value = assignment(aiscene->mAnimations[0]->mChannels[i]->mPositionKeys[j].mValue);
				keyframeNode->data->positionKeys.push_back(vectorKey);
			}
			for (unsigned int j = 0; j < aiscene->mAnimations[0]->mChannels[i]->mNumRotationKeys; j++) {
				QuaternionKey quaternionKey;
				quaternionKey.time = aiscene->mAnimations[0]->mChannels[i]->mRotationKeys[j].mTime;
				quaternionKey.value = assignment(aiscene->mAnimations[0]->mChannels[i]->mRotationKeys[j].mValue);
				keyframeNode->data->rotationKeys.push_back(quaternionKey);
			}
			for (unsigned int j = 0; j < aiscene->mAnimations[0]->mChannels[i]->mNumScalingKeys; j++) {
				VectorKey vectorKey;
				vectorKey.time = aiscene->mAnimations[0]->mChannels[i]->mScalingKeys[j].mTime;
				vectorKey.value = assignment(aiscene->mAnimations[0]->mChannels[i]->mScalingKeys[j].mValue);
				keyframeNode->data->scalingKeys.push_back(vectorKey);
			}
			break;
		}
	}

	// check children nodes
	for (unsigned int i = 0; i < ainode->mNumChildren; i++) {
		keyframeNode->children.push_back(new Node<Keyframe>(ainode->mChildren[i]->mName.data));
		this->processNode(keyframeNode->children[i], ainode->mChildren[i], aiscene);
	}
}


/*------------------------------------------------------------------------------
< process pose >
go through the keyframe node tree
-----------------------------------------------------------------------------*/
void Animation::processPose(std::vector<glm::mat4>& pose, Node<Keyframe>* keyframeNode, const Node<Bone>* boneNode, glm::mat4 parentTransformation) {

	if (keyframeNode->data && this->blendFactor >= 1.0) {
		// Interpolate scaling and generate scaling transformation matrix
		boneNode->data->scaling = this->calcInterpolatedScaling(keyframeNode->data);
		glm::mat4 scalingMatrix = glm::scale(boneNode->data->scaling);

		// Interpolate rotation and generate rotation transformation matrix
		boneNode->data->rotation = this->calcInterpolatedRotation(keyframeNode->data);
		glm::mat4 rotationMatrix = glm::mat4_cast(boneNode->data->rotation);

		// Interpolate translation and generate translation transformation matrix
		boneNode->data->translation = this->calcInterpolatedPosition(keyframeNode->data);
		glm::mat4 translationMatrix = glm::translate(boneNode->data->translation);

		// Combine the above transformations
		boneNode->data->nodeTransformation = translationMatrix * rotationMatrix * scalingMatrix;
	}

	if (keyframeNode->data && this->blendFactor < 1.0) {
		// Interpolate scaling and generate scaling transformation matrix
		glm::vec3 scaling = this->calcInterpolatedScaling(keyframeNode->data);
		boneNode->data->scaling = glm::mix(boneNode->data->scaling, scaling, this->blendFactor);
		glm::mat4 scalingMatrix = glm::scale(boneNode->data->scaling);

		// Interpolate rotation and generate rotation transformation matrix (need to normalize the slerp value?)
		glm::quat rotation = this->calcInterpolatedRotation(keyframeNode->data);
		boneNode->data->rotation = glm::slerp(boneNode->data->rotation, rotation, this->blendFactor);
		glm::mat4 rotationMatrix = glm::mat4_cast(boneNode->data->rotation);

		// Interpolate translation and generate translation transformation matrix
		glm::vec3 translation = this->calcInterpolatedPosition(keyframeNode->data);
		boneNode->data->translation = glm::mix(boneNode->data->translation, translation, this->blendFactor);
		glm::mat4 translationMatrix = glm::translate(boneNode->data->translation);

		// Combine the above transformations
		boneNode->data->nodeTransformation = translationMatrix * rotationMatrix * scalingMatrix;
	}

	glm::mat4 globalTransformation = parentTransformation * boneNode->data->nodeTransformation;

	// set pose
	if(boneNode->data->haveBone) {
		pose[boneNode->data->index] = globalTransformation * boneNode->data->offset;
	}
	// process pose children nodes
	for (unsigned int i = 0 ; i < keyframeNode->children.size() ; i++) {
		this->processPose(pose, keyframeNode->children[i], boneNode->children[i], globalTransformation);
	}
}


/*------------------------------------------------------------------------------
< find current keyframe index >
-----------------------------------------------------------------------------*/
void Animation::findPosition(Keyframe* keyframe) {
	for (unsigned int i = keyframe->currentPositionIndex ; i < keyframe->positionKeys.size() - 1 ; i++) {
		if (this->animationTimeInTicks >= keyframe->positionKeys[i].time && this->animationTimeInTicks < keyframe->positionKeys[i + 1].time) {
			keyframe->currentPositionIndex = i;
			return;
		}
	}
	keyframe->currentPositionIndex = 0;
}

void Animation::findRotation(Keyframe* keyframe) {
	for (unsigned int i = keyframe->currentRotationIndex ; i < keyframe->rotationKeys.size() - 1 ; i++) {
		if (this->animationTimeInTicks >= keyframe->rotationKeys[i].time && this->animationTimeInTicks < keyframe->rotationKeys[i + 1].time) {
			keyframe->currentRotationIndex = i;
			return;
		}
	}
	keyframe->currentRotationIndex = 0;
}

void Animation::findScaling(Keyframe* keyframe) {
	for (unsigned int i = keyframe->currentScalingIndex ; i < keyframe->scalingKeys.size() - 1 ; i++) {
		if (this->animationTimeInTicks >= keyframe->scalingKeys[i].time && this->animationTimeInTicks < keyframe->scalingKeys[i + 1].time) {
			keyframe->currentScalingIndex = i;
			return;
		}
	}
	keyframe->currentScalingIndex = 0;
}


/*------------------------------------------------------------------------------
< calculate interpolate transformation >
-----------------------------------------------------------------------------*/
glm::vec3 Animation::calcInterpolatedPosition(Keyframe* keyframe) {
	// need at least two values to interpolate
	if (keyframe->positionKeys.size() == 1) {
		return keyframe->positionKeys[0].value;
	}
	// find current keyframe index
	this->findPosition(keyframe);
	unsigned int nextPositionIndex = (keyframe->currentPositionIndex + 1);
	// calculate blend factor
	float deltaTime = keyframe->positionKeys[nextPositionIndex].time - keyframe->positionKeys[keyframe->currentPositionIndex].time;
	float factor = (this->animationTimeInTicks - keyframe->positionKeys[keyframe->currentPositionIndex].time) / deltaTime;
	// interpolate transformation
	return glm::mix(keyframe->positionKeys[keyframe->currentPositionIndex].value, keyframe->positionKeys[nextPositionIndex].value, factor);
}

glm::quat Animation::calcInterpolatedRotation(Keyframe* keyframe) {
	// need at least two values to interpolate
	if (keyframe->rotationKeys.size() == 1) {
		return keyframe->rotationKeys[0].value;
	}
	// find current keyframe index
	this->findRotation(keyframe);
	unsigned int nextRotationIndex = (keyframe->currentRotationIndex + 1);
	// calculate blend factor
	float deltaTime = keyframe->rotationKeys[nextRotationIndex].time - keyframe->rotationKeys[keyframe->currentRotationIndex].time;
	float factor = (this->animationTimeInTicks - keyframe->rotationKeys[keyframe->currentRotationIndex].time) / deltaTime;
	// interpolate transformation
	return glm::slerp(keyframe->rotationKeys[keyframe->currentRotationIndex].value, keyframe->rotationKeys[nextRotationIndex].value, factor);
}

glm::vec3 Animation::calcInterpolatedScaling(Keyframe* keyframe) {
	// need at least two values to interpolate
	if (keyframe->scalingKeys.size() == 1) {
		return keyframe->scalingKeys[0].value;
	}
	// find current keyframe index
	this->findScaling(keyframe);
	unsigned int nextScalingIndex = (keyframe->currentScalingIndex + 1);
	// calculate blend factor
	float deltaTime = keyframe->scalingKeys[nextScalingIndex].time - keyframe->scalingKeys[keyframe->currentScalingIndex].time;
	float factor = (this->animationTimeInTicks - keyframe->scalingKeys[keyframe->currentScalingIndex].time) / deltaTime;
	// interpolate transformation
	return glm::mix(keyframe->scalingKeys[keyframe->currentScalingIndex].value, keyframe->scalingKeys[nextScalingIndex].value, factor);
}
