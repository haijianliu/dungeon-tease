
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Model::Model() {

}

Model::Model(unsigned int attributeType, const char* path) {
	this->attributeType = attributeType;
	this->load(path);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Model::~Model() {
	delete this->boneNode;
	deleteVector(this->meshes);
	deleteVector(this->animations);
}


/*------------------------------------------------------------------------------
< load animation >
loads a model with supported ASSIMP extensions from file and stores the resulting animation keyframes in a node tree.
------------------------------------------------------------------------------*/
void Model::addAnimation(Animation* animation) {
	this->animations.push_back(animation);
}


/*------------------------------------------------------------------------------
< update pose >
update pose data with animations keyframes data and the given time in seconds
------------------------------------------------------------------------------*/
void Model::updatePose(unsigned int animationIndex, float timeInSeconds) {
	// animation always starts from the beginning
	if (this->currentAnimation != animationIndex) {
		this->animations[animationIndex]->reset(timeInSeconds);
		this->currentAnimation = animationIndex;
	}

	this->animations[animationIndex]->updatePose(this->pose, this->boneNode, timeInSeconds);
}


/*------------------------------------------------------------------------------
< set position uniform >
------------------------------------------------------------------------------*/
void Model::setPoseUniform(Shader* shader) {
	for (unsigned int i = 0 ; i < this->pose.size() ; i++) {
		shader->setMat4(("bones[" + std::to_string(i) + "]").c_str(), this->pose[i]);
	}
}


/*------------------------------------------------------------------------------
< draw >
------------------------------------------------------------------------------*/
void Model::draw() {
	for(unsigned int i = 0; i < this->meshes.size(); i++) this->meshes[i]->draw();
}

void Model::drawBounding() {
	for(unsigned int i = 0; i < this->meshes.size(); i++) this->meshes[i]->drawBounding();
}


/*------------------------------------------------------------------------------
< load model >
loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
------------------------------------------------------------------------------*/
void Model::load(const char* path) {
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* aiscene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_LimitBoneWeights);
	// check for errors
	if(!aiscene || aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiscene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// process assimp root node recursively
	this->boneNode = new Node<Bone>(aiscene->mRootNode->mName.data);
	this->boneNode->data = new Bone();
	this->boneNode->data->nodeTransformation = assignment(aiscene->mRootNode->mTransformation);
	this->processNode(aiscene->mRootNode, this->boneNode, aiscene);
}


/*------------------------------------------------------------------------------
< process node >
processes a node in a recursive function
the node object only contains indices to index the actual objects in the scene
the scene contains all the data
Processes each individual mesh located at the node and repeats this process on its children nodes (if any)
Processes the bone node heirarchy located at the node and calculate the final transformation
------------------------------------------------------------------------------*/
void Model::processNode(aiNode* ainode, Node<Bone>* node, const aiScene* aiscene) {
	/* if found a mesh */
	// process each mesh located at the current node
	for (unsigned int i = 0; i < ainode->mNumMeshes; i++) {
		aiMesh* mesh = aiscene->mMeshes[ainode->mMeshes[i]];
		this->meshes.push_back(new Mesh(mesh, &this->pose, this->attributeType));
	}
	// save the node heirarchy and all the transformation matrices and names
	node->data->nodeTransformation = assignment(ainode->mTransformation);
	// only support one mesh model !
	for (unsigned int i = 0; i < aiscene->mMeshes[0]->mNumBones; i ++) {
		if (node->name == aiscene->mMeshes[0]->mBones[i]->mName.data) {
			node->data->haveBone = true;
			node->data->index = i;
			node->data->offset = assignment(aiscene->mMeshes[0]->mBones[i]->mOffsetMatrix);
			break;
		}
	}

	/* look for children */
	// recursively process each of the children nodes
	for (unsigned int i = 0; i < ainode->mNumChildren; i++) {
		node->children.push_back(new Node<Bone>(ainode->mChildren[i]->mName.data));
		node->children[i]->parent = node;
		node->children[i]->data = new Bone();
		this->processNode(ainode->mChildren[i], node->children[i], aiscene);
	}
}
