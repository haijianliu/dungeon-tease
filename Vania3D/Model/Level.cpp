
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Level::Level(const char* path) {
	this->load(path);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Level::~Level() {
	delete this->modelNode;
}


/*------------------------------------------------------------------------------
< load model >
loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
------------------------------------------------------------------------------*/
void Level::load(const char* path) {
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* aiscene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights);
	// check for errors
	if(!aiscene || aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiscene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	// process assimp root node recursively
	this->modelNode = new Node<ModelInfo>(aiscene->mRootNode->mName.data);
	this->modelNode->data = new ModelInfo();
	this->processNode(aiscene->mRootNode, this->modelNode, aiscene);
}


/*------------------------------------------------------------------------------
< process node >
processes a node in a recursive function
the node object only contains indices to index the actual objects in the scene
the scene contains all the data
Processes each individual mesh located at the node and repeats this process on its children nodes (if any)
Processes the bone node heirarchy located at the node and calculate the final transformation
------------------------------------------------------------------------------*/
void Level::processNode(aiNode* ainode, Node<ModelInfo>* node, const aiScene* aiscene) {
	// save the node heirarchy and all the transformation matrices and names
	node->data->nodeTransformation = assignment(ainode->mTransformation);

	/* look for children */
	// recursively process each of the children nodes
	for (unsigned int i = 0; i < ainode->mNumChildren; i++) {
		node->children.push_back(new Node<ModelInfo>(ainode->mChildren[i]->mName.data));
		node->children[i]->parent = node;
		node->children[i]->data = new ModelInfo();
		this->processNode(ainode->mChildren[i], node->children[i], aiscene);
	}
}


void Level::createGameObjects(Scene* scene) {
	Game* game = Game::getInstance();
	glm::mat4 parentTransformation = glm::scale(glm::vec3(0.05));
	this->processNode(this->modelNode, parentTransformation, game, scene);
}

void Level::processNode(Node<ModelInfo>* node, glm::mat4 parentTransformation, Game* game, Scene* scene) {
	// create GameObject
	glm::mat4 globalTransformation = parentTransformation * node->data->nodeTransformation;
	std::string modelName = node->name.substr(0,node->name.rfind("."));
	Model* model = game->resources->getModel(modelName);
	if (model != nullptr) {
		GameObject* gameObject = new GameObject();
		Transform* transform = gameObject->addComponent<Transform>();
		transform->model = globalTransformation;
		MeshRenderer* meshRenderer = gameObject->addComponent<MeshRenderer>();
		meshRenderer->model = model;
		meshRenderer->materials.push_back(game->resources->getMaterial(modelName));
		scene->addGameObject(node->name.c_str(), gameObject);
	}

	for (unsigned int i = 0; i < node->children.size(); i++)
		this->processNode(node->children[i], globalTransformation, game, scene);
}
