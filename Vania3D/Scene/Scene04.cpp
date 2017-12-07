
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene04::Scene04() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene04::~Scene04() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void Scene04::start() {
	Game* game = Game::getInstance();
	Resources* resources = game->resources;
	
	// sky
	resources->loadShader("sky", "./Assets/Shaders/Vertex/static_2_locations_sky.vs.glsl", "./Assets/Shaders/Fragment/color_1_passes_sky.fs.glsl");
	resources->loadTexture("sky", "./Assets/Models/Basic/sky.tga");
	resources->loadModel("sky", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Basic/sky.fbx");
	resources->createMaterial("sky", resources->getShader("sky"));
	resources->getMaterial("sky")->addTexture("albedoMap", resources->getTexture("sky"));
	
	GameObject* sky = new GameObject();
	Transform* skyTransform = sky->addComponent<Transform>();
	skyTransform->rotation = glm::rotation(glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));
	skyTransform->scale = glm::vec3(100);
	skyTransform->updateModel();
	MeshRenderer* skyMeshRenderer = sky->addComponent<MeshRenderer>();
	skyMeshRenderer->renderLayer = RENDER_LAYER_FX;
	skyMeshRenderer->model = resources->getModel("sky");
	skyMeshRenderer->materials.push_back(resources->getMaterial("sky"));
	this->addGameObject("sky", sky);
	
	// shaders
	resources->loadShader("Library", "./Assets/Shaders/Vertex/static_3_locations.vs.glsl", "./Assets/Shaders/Fragment/mrca_4_passes.fs.glsl",  "./Assets/Shaders/Functions/getNormalFromMap.fs.glsl");
	
	// textures
	resources->loadTexture("ST_Arch01_basecolor", "./Assets/Models/Library/Textures/ST_Arch01_basecolor.TGA");
	resources->loadTexture("ST_Arch01_normal", "./Assets/Models/Library/Textures/ST_Arch01_normal.TGA");
	resources->loadTexture("ST_Arch01_mask", "./Assets/Models/Library/Textures/ST_Arch01_mask.TGA");
	resources->loadTexture("ST_Arch02_basecolor", "./Assets/Models/Library/Textures/ST_Arch02_basecolor.TGA");
	resources->loadTexture("ST_Arch02_normal", "./Assets/Models/Library/Textures/ST_Arch02_normal.TGA");
	resources->loadTexture("ST_Arch02_mask", "./Assets/Models/Library/Textures/ST_Arch02_mask.TGA");
	resources->loadTexture("ST_BookShelf_Pillar01_basecolor", "./Assets/Models/Library/Textures/ST_BookShelf_Pillar01_basecolor.TGA");
	resources->loadTexture("ST_BookShelf_Pillar01_normal", "./Assets/Models/Library/Textures/ST_BookShelf_Pillar01_normal.TGA");
	resources->loadTexture("ST_BookShelf_Pillar01_roughness", "./Assets/Models/Library/Textures/ST_BookShelf_Pillar01_roughness.TGA");
	resources->loadTexture("ST_BookShelf02_basecolor", "./Assets/Models/Library/Textures/ST_BookShelf02_basecolor.TGA");
	resources->loadTexture("ST_BookShelf02_normal", "./Assets/Models/Library/Textures/ST_BookShelf02_normal.TGA");
	resources->loadTexture("ST_BookShelf02_roughness", "./Assets/Models/Library/Textures/ST_BookShelf02_roughness.TGA");
	resources->loadTexture("ST_Floor1F_01_basecolor", "./Assets/Models/Library/Textures/ST_Floor1F_01_basecolor.TGA");
	resources->loadTexture("ST_Floor1F_01_normal", "./Assets/Models/Library/Textures/ST_Floor1F_01_normal.TGA");
	resources->loadTexture("ST_Floor1F_01_mask", "./Assets/Models/Library/Textures/ST_Floor1F_01_mask.TGA");
	resources->loadTexture("ST_Floor1F_02_basecolor", "./Assets/Models/Library/Textures/ST_Floor1F_02_basecolor.TGA");
	resources->loadTexture("ST_Floor1F_02_normal", "./Assets/Models/Library/Textures/ST_Floor1F_02_normal.TGA");
	resources->loadTexture("ST_Floor1F_02_mask", "./Assets/Models/Library/Textures/ST_Floor1F_02_mask.TGA");
	resources->loadTexture("ST_Floor2F_basecolor", "./Assets/Models/Library/Textures/ST_Floor2F_basecolor.TGA");
	resources->loadTexture("ST_Floor2F_normal", "./Assets/Models/Library/Textures/ST_Floor2F_normal.TGA");
	resources->loadTexture("ST_Floor2F_mask", "./Assets/Models/Library/Textures/ST_Floor2F_mask.TGA");
	resources->loadTexture("ST_Floor2F_Cor_basecolor", "./Assets/Models/Library/Textures/ST_Floor2F_Cor_basecolor.TGA");
	resources->loadTexture("ST_Floor2F_Cor_normal", "./Assets/Models/Library/Textures/ST_Floor2F_Cor_normal.TGA");
	resources->loadTexture("ST_Floor2F_Cor_roughness", "./Assets/Models/Library/Textures/ST_Floor2F_Cor_roughness.TGA");
	resources->loadTexture("ST_Handrail01_basecolor", "./Assets/Models/Library/Textures/ST_Handrail01_basecolor.TGA");
	resources->loadTexture("ST_Handrail01_normal", "./Assets/Models/Library/Textures/ST_Handrail01_normal.TGA");
	resources->loadTexture("ST_Handrail01_roughness", "./Assets/Models/Library/Textures/ST_Handrail01_roughness.TGA");
	resources->loadTexture("ST_Pillar01_basecolor", "./Assets/Models/Library/Textures/ST_Pillar01_basecolor.TGA");
	resources->loadTexture("ST_Pillar01_normal", "./Assets/Models/Library/Textures/ST_Pillar01_normal.TGA");
	resources->loadTexture("ST_Pillar01_mask", "./Assets/Models/Library/Textures/ST_Pillar01_mask.TGA");
	resources->loadTexture("ST_Stair_BaseColor", "./Assets/Models/Library/Textures/ST_Stair_BaseColor.TGA");
	resources->loadTexture("ST_Stair_Normal", "./Assets/Models/Library/Textures/ST_Stair_Normal.TGA");
	resources->loadTexture("ST_Stair_Mask", "./Assets/Models/Library/Textures/ST_Stair_Mask.TGA");
	
	// models
	resources->loadModel("ST_Arch01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Arch01.FBX");
	resources->getModel("ST_Arch01")->materialNames.push_back("MI_Arch01");
	resources->loadModel("ST_Arch02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Arch02.FBX");
	resources->getModel("ST_Arch02")->materialNames.push_back("MI_Arch02");
	resources->getModel("ST_Arch02")->materialNames.push_back("MI_Arch01");
	resources->loadModel("ST_Arch03", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Arch03.FBX");
	resources->getModel("ST_Arch03")->materialNames.push_back("MI_Arch01");
	resources->loadModel("ST_Arch04", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Arch04.FBX");
	resources->getModel("ST_Arch04")->materialNames.push_back("MI_Arch01");
	resources->loadModel("ST_BookShelf_Pillar02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_BookShelf_Pillar02.FBX");
	resources->getModel("ST_BookShelf_Pillar02")->materialNames.push_back("MI_BookShelf_Pillar01");
	resources->loadModel("ST_BookShelf_Pillar04", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_BookShelf_Pillar04.FBX");
	resources->getModel("ST_BookShelf_Pillar04")->materialNames.push_back("MI_BookShelf02");
	resources->loadModel("ST_BookShelf02_2", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_BookShelf02_2.FBX");
	resources->getModel("ST_BookShelf02_2")->materialNames.push_back("MI_BookShelf02");
	resources->loadModel("ST_Floor1F_02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Floor1F_02.FBX");
	resources->getModel("ST_Floor1F_02")->materialNames.push_back("MI_Floor1F_02");
	resources->getModel("ST_Floor1F_02")->materialNames.push_back("MI_Floor1F_01");
	resources->loadModel("ST_Floor2F_Cor02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Floor2F_Cor02.FBX");
	resources->getModel("ST_Floor2F_Cor02")->materialNames.push_back("MI_Floor2F_Cor");
	resources->loadModel("ST_Floor2F_Stair02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Floor2F_Stair02.FBX");
	resources->getModel("ST_Floor2F_Stair02")->materialNames.push_back("MI_Pillar01");
	resources->loadModel("ST_Floor2F", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Floor2F.FBX");
	resources->getModel("ST_Floor2F")->materialNames.push_back("MI_Floor2F");
	resources->loadModel("ST_HandRail", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_HandRail.FBX");
	resources->getModel("ST_HandRail")->materialNames.push_back("MI_Handrail01");
	resources->loadModel("ST_HandRail02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_HandRail02.FBX");
	resources->getModel("ST_HandRail02")->materialNames.push_back("MI_Handrail01");
	resources->loadModel("ST_Pillar01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Pillar01.FBX");
	resources->getModel("ST_Pillar01")->materialNames.push_back("MI_Pillar01");
	resources->loadModel("ST_Stair", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Library/Meshes/ST_Stair.FBX");
	resources->getModel("ST_Stair")->materialNames.push_back("MI_Stair");
	
	
	// materials
	// MI_Arch01
	resources->createMaterial("MI_Arch01", resources->getShader("Library"));
	resources->getMaterial("MI_Arch01")->addTexture("albedoMap", resources->getTexture("ST_Arch01_basecolor"));
	resources->getMaterial("MI_Arch01")->addTexture("normalMap", resources->getTexture("ST_Arch01_normal"));
	resources->getMaterial("MI_Arch01")->addTexture("maskMap", resources->getTexture("ST_Arch01_mask"));
	// MI_Arch02
	resources->createMaterial("MI_Arch02", resources->getShader("Library"));
	resources->getMaterial("MI_Arch02")->addTexture("albedoMap", resources->getTexture("ST_Arch02_basecolor"));
	resources->getMaterial("MI_Arch02")->addTexture("normalMap", resources->getTexture("ST_Arch02_normal"));
	resources->getMaterial("MI_Arch02")->addTexture("maskMap", resources->getTexture("ST_Arch02_mask"));
	// MI_BookShelf02
	resources->createMaterial("MI_BookShelf02", resources->getShader("Library"));
	resources->getMaterial("MI_BookShelf02")->addTexture("albedoMap", resources->getTexture("ST_BookShelf02_basecolor"));
	resources->getMaterial("MI_BookShelf02")->addTexture("normalMap", resources->getTexture("ST_BookShelf02_normal"));
	resources->getMaterial("MI_BookShelf02")->addTexture("maskMap", resources->getTexture("ST_BookShelf02_roughness"));
	// MI_BookShelf_Pillar01
	resources->createMaterial("MI_BookShelf_Pillar01", resources->getShader("Library"));
	resources->getMaterial("MI_BookShelf_Pillar01")->addTexture("albedoMap", resources->getTexture("ST_BookShelf_Pillar01_basecolor"));
	resources->getMaterial("MI_BookShelf_Pillar01")->addTexture("normalMap", resources->getTexture("ST_BookShelf_Pillar01_normal"));
	resources->getMaterial("MI_BookShelf_Pillar01")->addTexture("maskMap", resources->getTexture("ST_BookShelf_Pillar01_roughness"));
	// MI_Floor1F_01
	resources->createMaterial("MI_Floor1F_01", resources->getShader("Library"));
	resources->getMaterial("MI_Floor1F_01")->addTexture("albedoMap", resources->getTexture("ST_Floor1F_01_basecolor"));
	resources->getMaterial("MI_Floor1F_01")->addTexture("normalMap", resources->getTexture("ST_Floor1F_01_normal"));
	resources->getMaterial("MI_Floor1F_01")->addTexture("maskMap", resources->getTexture("ST_Floor1F_01_mask"));
	// MI_Floor1F_02
	resources->createMaterial("MI_Floor1F_02", resources->getShader("Library"));
	resources->getMaterial("MI_Floor1F_02")->addTexture("albedoMap", resources->getTexture("ST_Floor1F_02_basecolor"));
	resources->getMaterial("MI_Floor1F_02")->addTexture("normalMap", resources->getTexture("ST_Floor1F_02_normal"));
	resources->getMaterial("MI_Floor1F_02")->addTexture("maskMap", resources->getTexture("ST_Floor1F_02_mask"));
	// MI_Floor2F
	resources->createMaterial("MI_Floor2F", resources->getShader("Library"));
	resources->getMaterial("MI_Floor2F")->addTexture("albedoMap", resources->getTexture("ST_Floor2F_basecolor"));
	resources->getMaterial("MI_Floor2F")->addTexture("normalMap", resources->getTexture("ST_Floor2F_Cor_normal"));
	resources->getMaterial("MI_Floor2F")->addTexture("maskMap", resources->getTexture("ST_Floor2F_mask"));
	// MI_Floor2F_Cor
	resources->createMaterial("MI_Floor2F_Cor", resources->getShader("Library"));
	resources->getMaterial("MI_Floor2F_Cor")->addTexture("albedoMap", resources->getTexture("ST_Floor2F_Cor_basecolor"));
	resources->getMaterial("MI_Floor2F_Cor")->addTexture("normalMap", resources->getTexture("ST_Floor2F_Cor_normal"));
	resources->getMaterial("MI_Floor2F_Cor")->addTexture("maskMap", resources->getTexture("ST_Floor2F_Cor_roughness"));
	// MI_Handrail01
	resources->createMaterial("MI_Handrail01", resources->getShader("Library"));
	resources->getMaterial("MI_Handrail01")->addTexture("albedoMap", resources->getTexture("ST_Handrail01_basecolor"));
	resources->getMaterial("MI_Handrail01")->addTexture("normalMap", resources->getTexture("ST_Handrail01_normal"));
	resources->getMaterial("MI_Handrail01")->addTexture("maskMap", resources->getTexture("ST_Handrail01_roughness"));
	// MI_Pillar01
	resources->createMaterial("MI_Pillar01", resources->getShader("Library"));
	resources->getMaterial("MI_Pillar01")->addTexture("albedoMap", resources->getTexture("ST_Pillar01_basecolor"));
	resources->getMaterial("MI_Pillar01")->addTexture("normalMap", resources->getTexture("ST_Pillar01_normal"));
	resources->getMaterial("MI_Pillar01")->addTexture("maskMap", resources->getTexture("ST_Pillar01_mask"));
	// MI_Stair
	resources->createMaterial("MI_Stair", resources->getShader("Library"));
	resources->getMaterial("MI_Stair")->addTexture("albedoMap", resources->getTexture("ST_Stair_BaseColor"));
	resources->getMaterial("MI_Stair")->addTexture("normalMap", resources->getTexture("ST_Stair_Normal"));
	resources->getMaterial("MI_Stair")->addTexture("maskMap", resources->getTexture("ST_Stair_Mask"));
	
	// camera
	GameObject* camera = new GameObject();
	camera->staticObject = false;
	camera->addComponent<Camera>();

	// player
	GameObject* player = new GameObject();
	player->staticObject = false;
	Transform* playerTransform = player->addComponent<Transform>();
	playerTransform->modelScale = glm::vec3(GLOBAL_SCALE);
	playerTransform->position = glm::vec3(0, 0, 0);
	PlayerController* playerController = player->addComponent<PlayerController>();
	playerController->camera = camera;
	CameraController* cameraController = player->addComponent<CameraController>();
	cameraController->camera = camera;
	this->addGameObject("player", player);
	
	// renderpass
	game->resources->loadShader("renderpass_combine_scene04", "./Assets/Shaders/Vertex/quad.vs.glsl", "./Assets/Shaders/RenderPassScene04/renderpass_combine.fs.glsl");
	game->resources->loadShader("ambient_pass_scene04", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPassScene04/renderpass_ambient_1_passes.fs.glsl");
	game->resources->loadShader("lighting_pass_scene04", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPassScene04/renderpass_lighting_1_passes.fs.glsl", "./Assets/Shaders/Functions/cookTorranceBRDF.fs.glsl");
	delete game->renderPass;
	game->renderPass = new RenderPass();
	game->renderPass->combineShader = game->resources->getShader("renderpass_combine_scene04");
	game->renderPass->ambientShader = game->resources->getShader("ambient_pass_scene04");
	game->renderPass->lightingShader = game->resources->getShader("lighting_pass_scene04");
	game->renderPass->start();
	
	// shadow
	GameObject* shadowTarget = new GameObject();
	Transform* shadowTargetTransform = shadowTarget->addComponent<Transform>();
	shadowTargetTransform->position = glm::vec3(0, 0, -7);
	shadowTargetTransform->updateModel();
	delete game->shadowMapping;
	game->shadowMapping = new ShadowMapping();
	game->shadowMapping->shader = resources->getShader("shadow_mapping_depth_static");
	game->shadowMapping->target = shadowTarget;
	game->shadowMapping->lightPositionOffset = glm::vec3(5, 5, -1);
	game->shadowMapping->nearPlane = 1;
	game->shadowMapping->farPlane = 20;
	game->shadowMapping->range = 15;
	game->shadowMapping->start();

	// camera target
	GameObject* cameraTarget = new GameObject();
	Transform* cameraTargetTransform = cameraTarget->addComponent<Transform>();
	Offset* cameraTargetOffset = cameraTarget->addComponent<Offset>();
	cameraTargetOffset->parent = playerTransform;
	cameraTargetOffset->offsetPosition = glm::vec3(0, 1, 0);
	this->addGameObject("cameraTarget", cameraTarget);

	// camera
	Transform* cameraTransform = camera->addComponent<Transform>();
	cameraTransform->position = glm::vec3(0.0,2.0,4.0);
	camera->getComponent<Camera>()->target = cameraTargetTransform;
	camera->addComponent<FrustumCulling>();
	this->mainCamera = camera;
	this->addGameObject("mainCamera", camera);

	// map
	Map* map = new Map(this, "./Assets/Models/Library/Maps/Map.fbx");
	delete map;
	
	// light
	GameObject* light[4];
	for (int i = 0; i < 4; i++) {
		light[i] = new GameObject();
		light[i]->staticObject = false;
		Transform* lightTransform = light[i]->addComponent<Transform>();
		lightTransform->modelScale = glm::vec3(5 * GLOBAL_SCALE);
		light[i]->addComponent<PointLight>();
		// for test
		MeshRenderer* lightMeshRenderer = light[i]->addComponent<MeshRenderer>();
		lightMeshRenderer->model = game->resources->getModel("sphere");
		lightMeshRenderer->materials.push_back(game->resources->getMaterial("simple"));
		this->addGameObject(("light" + std::to_string(i)).c_str(), light[i]);
	}
	light[0]->getComponent<Transform>()->position = glm::vec3(0, 2.5, -5);
	light[1]->getComponent<Transform>()->position = glm::vec3(0, 2.5, 0);
	light[2]->getComponent<Transform>()->position = glm::vec3(0, 5, -15);
	light[3]->getComponent<Transform>()->position = glm::vec3(0, 7.5, -25);
	light[0]->getComponent<PointLight>()->color = glm::vec3(1, 1, 1);
	light[0]->getComponent<PointLight>()->intensity = 5;
	light[1]->getComponent<PointLight>()->color = glm::vec3(1, 1, 1);
	light[1]->getComponent<PointLight>()->intensity = 5;
	light[2]->getComponent<PointLight>()->color = glm::vec3(1, 1, 1);
	light[2]->getComponent<PointLight>()->intensity = 5;
	light[3]->getComponent<PointLight>()->color = glm::vec3(1, 1, 1);
	light[3]->getComponent<PointLight>()->intensity = 5;
}

