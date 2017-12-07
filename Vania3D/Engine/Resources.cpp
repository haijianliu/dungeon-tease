
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Resources::Resources() {

}

Resources* Resources::getInstance() {
	static Resources* resources = new Resources();
	return resources;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Resources::~Resources() {
	deleteMap(this->shaders);
	deleteMap(this->models);
	deleteMap(this->textures);
	deleteMap(this->lightProbes);
	deleteMap(this->materials);
	delete this->quad;
	delete this->quadinstance2vec3;
	delete this->skybox;
}


/*------------------------------------------------------------------------------
< start > before GameObject defaultStart()
------------------------------------------------------------------------------*/
void Resources::start() {
	/* Meshes
	..............................................................................*/
	this->quad = new Quad();
	this->quadinstance2vec3 = new QuadInstance2vec3();
	this->skybox = new Skybox();

	/* Shader
	..............................................................................*/
	// renderpass
	this->loadShader("renderpass_combine", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_combine.fs.glsl");
	this->loadShader("ambient_pass", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_ambient_1_passes.fs.glsl");
	this->loadShader("lighting_pass", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_lighting_1_passes.fs.glsl", "./Assets/Shaders/Functions/cookTorranceBRDF.fs.glsl");
	this->loadShader("shadow_pass", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_shadow_1_passes.fs.glsl", "./Assets/Shaders/Functions/shadowMapping.fs.glsl");
	this->loadShader("ssao_pass", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_ssao_1_passes.fs.glsl");

	// fx
	this->loadShader("fx_uv_animation", "./Assets/Shaders/Vertex/instance_7_locations_fx_animation.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_fx_1_passes.fs.glsl");
	this->loadShader("fx_image", "./Assets/Shaders/Vertex/instance_7_locations_fx.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_fx_1_passes.fs.glsl");

	// shadow mapping
	this->loadShader("shadow_mapping_depth", "./Assets/Shaders/Vertex/bones_3_locations_shadowmapping.vs.glsl",  "./Assets/Shaders/Fragment/null.fs.glsl");
	this->loadShader("shadow_mapping_depth_static", "./Assets/Shaders/Vertex/static_1_locations_shadowmapping.vs.glsl",  "./Assets/Shaders/Fragment/null.fs.glsl");

	// ibl
	this->loadShader("equirectangularToCubemap", "./Assets/Shaders/cubemap.vs.glsl",  "./Assets/Shaders/equirectangularToCubemap.fs.glsl");
	this->loadShader("irradianceConvolution", "./Assets/Shaders/cubemap.vs.glsl",  "./Assets/Shaders/irradianceConvolution.fs.glsl");
	this->loadShader("prefilter", "./Assets/Shaders/cubemap.vs.glsl",  "./Assets/Shaders/prefilter.fs.glsl");
	this->loadShader("brdf", "./Assets/Shaders/brdf.vs.glsl",  "./Assets/Shaders/brdf.fs.glsl");

	// other
	this->loadShader("deferred_pbr_bone", "./Assets/Shaders/Vertex/bones_5_locations.vs.glsl",  "./Assets/Shaders/Fragment/bgra_to_mrca_4_passes.fs.glsl", "./Assets/Shaders/Functions/getNormalFromMap.fs.glsl");
	this->loadShader("simple", "./Assets/Shaders/Vertex/static_1_locations.vs.glsl", "./Assets/Shaders/Fragment/color_white_1_passes.fs.glsl");
	this->createMaterial("simple", this->getShader("simple"));
	this->loadShader("renderpass_color_1_passes", "./Assets/Shaders/Vertex/quad.vs.glsl",  "./Assets/Shaders/RenderPass/renderpass_color_1_passes.fs.glsl");

	/* Model
	..............................................................................*/
	this->loadModel("player", MESH_ATTRIBUTE_BONE, "./Assets/Models/Ganfaul/mixamo_model.fbx");
	this->getModel("player")->addAnimation(new Animation("./Assets/Models/Ganfaul/mixamo_idle_stay.fbx"));
	this->getModel("player")->addAnimation(new Animation("./Assets/Models/Ganfaul/mixamo_idle_look.fbx"));
	this->getModel("player")->addAnimation(new Animation("./Assets/Models/Ganfaul/mixamo_walk.fbx"));
	this->getModel("player")->addAnimation(new Animation("./Assets/Models/Ganfaul/mixamo_run.fbx"));
	this->getModel("player")->addAnimation(new Animation("./Assets/Models/Ganfaul/mixamo_swiping.fbx"));
	this->loadTexture("player_albedo", "./Assets/Models/Ganfaul/Ganfaul_diffuse.TGA");
	this->loadTexture("player_normal", "./Assets/Models/Ganfaul/Ganfaul_normal.TGA");
	this->loadTexture("player_mask", "./Assets/Models/Ganfaul/Ganfaul_mask.TGA");
	this->createMaterial("player", this->getShader("deferred_pbr_bone"));
	this->getMaterial("player")->addTexture("albedoMap", this->getTexture("player_albedo"));
	this->getMaterial("player")->addTexture("normalMap", this->getTexture("player_normal"));
	this->getMaterial("player")->addTexture("maskMap", this->getTexture("player_mask"));
	this->getMaterial("player")->twoSides = true;

	// sphere
	this->loadModel("sphere", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/Basic/sphere.fbx");

	/* LightProbe
	..............................................................................*/
	// this->loadLightProbe("hdr", "./Assets/Textures/HDR/WinterForest_Ref.hdr");
	// this->loadLightProbe("hdr", "./Assets/Textures/HDR/Road_to_MonumentValley_8k.jpg");
	// this->loadLightProbe("hdr", "./Assets/Textures/HDR/Stadium_Center_8k.jpg");
	this->loadLightProbe("hdr", "./Assets/Models/InfinityBladeGrassLands/Maps/LevelContent/HDRI/HDRI_Epic_Courtyard_Daylight.HDR");
	// this->loadLightProbe("hdr", "./Assets/Textures/HDR/test.jpg");

}


/*------------------------------------------------------------------------------
< Load & Get >
------------------------------------------------------------------------------*/
void Resources::loadShader(const char* name, const char* vertexPath, const char* fragmentPath) {
	Shader* shader = new Shader();
	shader->addVertexCode(vertexPath);
	shader->addFragmentCode(fragmentPath);
	shader->complie();
	this->shaders.insert(std::make_pair(name, shader));
}
void Resources::loadShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* functionPath) {
	Shader* shader = new Shader();
	shader->addVertexCode(vertexPath);
	shader->addFragmentCode(fragmentPath);
	shader->addFragmentCode(functionPath);
	shader->complie();
	this->shaders.insert(std::make_pair(name, shader));
}
void Resources::loadShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* functionPath1, const char* functionPath2) {
	Shader* shader = new Shader();
	shader->addVertexCode(vertexPath);
	shader->addFragmentCode(fragmentPath);
	shader->addFragmentCode(functionPath1);
	shader->addFragmentCode(functionPath2);
	shader->complie();
	this->shaders.insert(std::make_pair(name, shader));
}
Shader* Resources::getShader(const char* name) {
	auto it = this->shaders.find(name);
	if (it != this->shaders.end()) {
		return this->shaders[name];
	}
	else {
		std::cout << "[Resources] no shader named " << name << '\n';
		return nullptr;
	}
}
void Resources::loadTexture(const char* name, const char* path) {
	this->textures.insert(std::make_pair(name, new Texture(path)));
}
Texture* Resources::getTexture(const char* name) {
	auto it = this->textures.find(name);
	if (it != this->textures.end()) {
		return this->textures[name];
	}
	else {
		std::cout << "[Resources] no texture named " << name << '\n';
		return nullptr;
	}
}
void Resources::loadModel(std::string name, unsigned int attributeType, const char* path) {
	this->models.insert(std::make_pair(name, new Model(attributeType, path)));
}
Model* Resources::getModel(std::string name) {
	auto it = this->models.find(name);
	if (it != this->models.end()) {
		return this->models[name];
	}
	else {
		std::cout << "[Resources] no model named " << name << '\n';
		return nullptr;
	}
}
void Resources::loadLightProbe(const char* name, const char* path) {
	this->lightProbes.insert(std::make_pair(name, new LightProbe(path)));
}
LightProbe* Resources::getLightProbe(const char* name) {
	auto it = this->lightProbes.find(name);
	if (it != this->lightProbes.end()) {
		return this->lightProbes[name];
	}
	else {
		std::cout << "[Resources] no lightProbe named " << name << '\n';
		return nullptr;
	}
}
void Resources::createMaterial(std::string name, Shader* shader) {
	this->materials.insert(std::make_pair(name, new Material(shader)));
}
Material* Resources::getMaterial(std::string name) {
	auto it = this->materials.find(name);
	if (it != this->materials.end()) {
		return this->materials[name];
	}
	else {
		std::cout << "[Resources] no material named " << name << '\n';
		return nullptr;
	}
}
