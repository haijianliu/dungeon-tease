
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene03::Scene03() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene03::~Scene03() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void Scene03::start() {
	Game* game = Game::getInstance();
	Resources* resources = game->resources;


	/* FantasyDungeon
	 ..............................................................................*/
	// shaders
	resources->loadShader("FantasyDungeonSRM", "./Assets/Shaders/Vertex/static_3_locations.vs.glsl",  "./Assets/Shaders/FantasyDungeon/bgra_to_mrca_4_passes.fs.glsl", "./Assets/Shaders/Functions/getNormalFromMap.fs.glsl");
	resources->loadShader("FantasyDungeonWet", "./Assets/Shaders/Vertex/static_3_locations.vs.glsl",  "./Assets/Shaders/FantasyDungeon/bgra_to_mrca_wet_4_passes.fs.glsl", "./Assets/Shaders/Functions/getNormalFromMap.fs.glsl");

	// BaseTexture
	resources->loadTexture("Mask1", "./Assets/Models/FantasyDungeon/Textures/BaseTexture/Mask1.TGA");

	// FX
	resources->loadTexture("fx_fire_D", "./Assets/Models/FantasyDungeon/Textures/FX/fx_fire_D.TGA");
	resources->createMaterial("fx_fire", resources->getShader("fx_uv_animation"));
	resources->getMaterial("fx_fire")->addTexture("albedoMap", resources->getTexture("fx_fire_D"));
	resources->loadTexture("fx_fire_smoke_D", "./Assets/Models/FantasyDungeon/Textures/FX/fx_fire_smoke_D.TGA");
	resources->createMaterial("fx_fire_smoke", resources->getShader("fx_image"));
	resources->getMaterial("fx_fire_smoke")->addTexture("albedoMap", resources->getTexture("fx_fire_smoke_D"));
	resources->loadTexture("fx_fire_drop_D", "./Assets/Models/FantasyDungeon/Textures/FX/fx_fire_drop_D.TGA");
	resources->createMaterial("fx_fire_drop", resources->getShader("fx_image"));
	resources->getMaterial("fx_fire_drop")->addTexture("albedoMap", resources->getTexture("fx_fire_drop_D"));
	resources->loadTexture("fx_fire_spark_D", "./Assets/Models/FantasyDungeon/Textures/FX/fx_fire_spark_D.TGA");
	resources->createMaterial("fx_fire_spark", resources->getShader("fx_image"));
	resources->getMaterial("fx_fire_spark")->addTexture("albedoMap", resources->getTexture("fx_fire_spark_D"));

	// Arch
	resources->loadModel("Arch01", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Arch/Arch01.FBX");
	resources->getModel("Arch01")->materialNames.push_back("Arch");
	resources->getModel("Arch01")->materialNames.push_back("brick2");
	resources->loadTexture("Arch_D", "./Assets/Models/FantasyDungeon/Textures/Arch/Arch_D.TGA");
	resources->loadTexture("Arch_N", "./Assets/Models/FantasyDungeon/Textures/Arch/Arch_N.TGA");

	// BrickDamege
	resources->loadModel("Brick01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/BrickDamege/Brick01.FBX");
	resources->getModel("Brick01")->materialNames.push_back("BrickDamege");
	resources->loadModel("Brick02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/BrickDamege/Brick02.FBX");
	resources->getModel("Brick02")->materialNames.push_back("BrickDamege");
	resources->loadModel("rock01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/BrickDamege/rock01.FBX");
	resources->getModel("rock01")->materialNames.push_back("BrickDamege");
	resources->loadModel("rock02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/BrickDamege/rock02.FBX");
	resources->getModel("rock02")->materialNames.push_back("BrickDamege");
	resources->loadModel("rock03", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/BrickDamege/rock03.FBX");
	resources->getModel("rock03")->materialNames.push_back("BrickDamege");
	resources->loadTexture("BrickDamage_D", "./Assets/Models/FantasyDungeon/Textures/BrickDamege/BrickDamage_D.TGA");
	resources->loadTexture("BrickDamage_N", "./Assets/Models/FantasyDungeon/Textures/BrickDamege/BrickDamage_N.TGA");
	resources->loadTexture("BrickDamage_SRM", "./Assets/Models/FantasyDungeon/Textures/BrickDamege/BrickDamage_SRM.TGA");

	// Chandelier
	resources->loadModel("torch03", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Chandelier/torch03.FBX");
	resources->getModel("torch03")->materialNames.push_back("Chandelier");
	resources->loadTexture("chandelier_D", "./Assets/Models/FantasyDungeon/Textures/Chandelier/chandelier_D.TGA");
	resources->loadTexture("chandelier_N", "./Assets/Models/FantasyDungeon/Textures/Chandelier/chandelier_N.TGA");
	resources->loadTexture("chandelier_SRM", "./Assets/Models/FantasyDungeon/Textures/Chandelier/chandelier_SRM.TGA");

	// Column
	resources->loadModel("Column02", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Column/Column02.FBX");
	resources->getModel("Column02")->materialNames.push_back("column");
	resources->loadModel("Column03", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Column/Column03.FBX");
	resources->getModel("Column03")->materialNames.push_back("column");
	resources->loadModel("Column04", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Column/Column04.FBX");
	resources->getModel("Column04")->materialNames.push_back("column");
	resources->loadTexture("Column_D", "./Assets/Models/FantasyDungeon/Textures/Column/Column_D.TGA");
	resources->loadTexture("Column_N", "./Assets/Models/FantasyDungeon/Textures/Column/Column_N.TGA");
	resources->loadTexture("Column_SRM", "./Assets/Models/FantasyDungeon/Textures/Column/Column_SRM.TGA");
	resources->loadTexture("Column_damage_D", "./Assets/Models/FantasyDungeon/Textures/Column/Column_damage_D.TGA");
	resources->loadTexture("Column_damage_N", "./Assets/Models/FantasyDungeon/Textures/Column/Column_damage_N.TGA");

	// Curbstone
	resources->loadModel("curbstone01_2", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone01_2.FBX");
	resources->getModel("curbstone01_2")->materialNames.push_back("curbstone");
	resources->getModel("curbstone01_2")->materialNames.push_back("pavement1");
	resources->loadModel("curbstone01_Door1", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone01_Door1.FBX");
	resources->getModel("curbstone01_Door1")->materialNames.push_back("curbstone");
	resources->getModel("curbstone01_Door1")->materialNames.push_back("pavement1");
	resources->loadModel("curbstone01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone01.FBX");
	resources->getModel("curbstone01")->materialNames.push_back("curbstone");
	resources->getModel("curbstone01")->materialNames.push_back("pavement1");
	resources->loadModel("curbstone02_2", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone02_2.FBX");
	resources->getModel("curbstone02_2")->materialNames.push_back("curbstone");
	resources->loadModel("curbstone02_2a", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone02_2a.FBX");
	resources->getModel("curbstone02_2a")->materialNames.push_back("curbstone");
	resources->loadModel("curbstone02_door1", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone02_door1.FBX");
	resources->getModel("curbstone02_door1")->materialNames.push_back("curbstone");
	resources->loadModel("curbstone02", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Curbstone/curbstone02.FBX");
	resources->getModel("curbstone02")->materialNames.push_back("curbstone");
	resources->loadTexture("curbstone_D", "./Assets/Models/FantasyDungeon/Textures/Curbstone/curbstone_D.TGA");
	resources->loadTexture("curbstone_N", "./Assets/Models/FantasyDungeon/Textures/Curbstone/curbstone_N.TGA");	resources->loadTexture("curbstone_SRM", "./Assets/Models/FantasyDungeon/Textures/Curbstone/curbstone_SRM.TGA");

	// Door
	resources->loadModel("Door02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Door/Door02.FBX");
	resources->getModel("Door02")->materialNames.push_back("Door1");
	resources->loadModel("DoorArch01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Door/DoorArch01.FBX");
	resources->getModel("DoorArch01")->materialNames.push_back("DoorArch");
	resources->loadTexture("Door1_D", "./Assets/Models/FantasyDungeon/Textures/Door/Door1_D.TGA");
	resources->loadTexture("Door1_N", "./Assets/Models/FantasyDungeon/Textures/Door/Door1_N.TGA");
	resources->loadTexture("Door1_SRM", "./Assets/Models/FantasyDungeon/Textures/Door/Door1_SRM.TGA");
	resources->loadTexture("DoorArch_D", "./Assets/Models/FantasyDungeon/Textures/Door/DoorArch_D.TGA");
	resources->loadTexture("DoorArch_N", "./Assets/Models/FantasyDungeon/Textures/Door/DoorArch_N.TGA");
	resources->loadTexture("DoorArch_SRM", "./Assets/Models/FantasyDungeon/Textures/Door/DoorArch_SRM.TGA");

	// Floor
	resources->loadModel("Floor01", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Floor/Floor01.FBX");
	resources->getModel("Floor01")->materialNames.push_back("pavement2");
	resources->loadTexture("Dirt_D", "./Assets/Models/FantasyDungeon/Textures/Floor/Dirt_D.TGA");
	resources->loadTexture("Dirt_N", "./Assets/Models/FantasyDungeon/Textures/Floor/Dirt_N.TGA");
	resources->loadTexture("Dirt_SRM", "./Assets/Models/FantasyDungeon/Textures/Floor/Dirt_SRM.TGA");
	resources->loadTexture("pavement1_D", "./Assets/Models/FantasyDungeon/Textures/Floor/pavement1_D.TGA");
	resources->loadTexture("pavement1_N", "./Assets/Models/FantasyDungeon/Textures/Floor/pavement1_N.TGA");
	resources->loadTexture("pavement1_SRM", "./Assets/Models/FantasyDungeon/Textures/Floor/pavement1_SRM.TGA");
	resources->loadTexture("pavement2_D", "./Assets/Models/FantasyDungeon/Textures/Floor/pavement2_D.TGA");
	resources->loadTexture("pavement2_N", "./Assets/Models/FantasyDungeon/Textures/Floor/pavement2_N.TGA");
	resources->loadTexture("pavement2_SRM", "./Assets/Models/FantasyDungeon/Textures/Floor/pavement2_SRM.TGA");
	resources->loadTexture("Sink_D", "./Assets/Models/FantasyDungeon/Textures/Floor/Sink_D.TGA");
	resources->loadTexture("Sink_N", "./Assets/Models/FantasyDungeon/Textures/Floor/Sink_N.TGA");
	resources->loadTexture("Sink_SRM", "./Assets/Models/FantasyDungeon/Textures/Floor/Sink_SRM.TGA");

	// Jail
	resources->loadTexture("Jail_D", "./Assets/Models/FantasyDungeon/Textures/Jail/Jail_D.TGA");
	resources->loadTexture("Jail_N", "./Assets/Models/FantasyDungeon/Textures/Jail/Jail_N.TGA");
	resources->loadTexture("Jail_SRM", "./Assets/Models/FantasyDungeon/Textures/Jail/Jail_SRM.TGA");

	// Roof
	resources->loadModel("Roof01", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Roof/Roof01.FBX");
	resources->getModel("Roof01")->materialNames.push_back("brick1");
	resources->getModel("Roof01")->materialNames.push_back("Roof");
	resources->loadModel("Roof03", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Roof/Roof03.FBX");
	resources->getModel("Roof03")->materialNames.push_back("brick1");
	resources->loadModel("Roof16", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Roof/Roof16.FBX");
	resources->getModel("Roof16")->materialNames.push_back("brick1");
	resources->getModel("Roof16")->materialNames.push_back("Roof");
	resources->loadModel("RoofBorder01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Roof/RoofBorder01.FBX");
	resources->getModel("RoofBorder01")->materialNames.push_back("Roof");
	resources->loadTexture("Roof_D", "./Assets/Models/FantasyDungeon/Textures/Roof/Roof_D.TGA");
	resources->loadTexture("Roof_N", "./Assets/Models/FantasyDungeon/Textures/Roof/Roof_N.TGA");

	// Stairs
	resources->loadModel("Railing01_1", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Stairs/Railing01_1.FBX");
	resources->getModel("Railing01_1")->materialNames.push_back("Stairs");
	resources->getModel("Railing01_1")->materialNames.push_back("Railing");
	resources->loadModel("Railing_base01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Stairs/Railing_base01.FBX");
	resources->getModel("Railing_base01")->materialNames.push_back("Stairs");
	resources->loadModel("Stairs01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Stairs/Stairs01.FBX");
	resources->getModel("Stairs01")->materialNames.push_back("Stairs");
	resources->getModel("Stairs01")->materialNames.push_back("brick2");
	resources->loadModel("StairsDamage01", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Stairs/StairsDamage01.FBX");
	resources->getModel("StairsDamage01")->materialNames.push_back("Stairs");
	resources->getModel("StairsDamage01")->materialNames.push_back("column_damage");
	resources->getModel("StairsDamage01")->materialNames.push_back("brick2");
	resources->loadTexture("Railing_D", "./Assets/Models/FantasyDungeon/Textures/Stairs/Railing_D.TGA");
	resources->loadTexture("Railing_N", "./Assets/Models/FantasyDungeon/Textures/Stairs/Railing_N.TGA");
	resources->loadTexture("Stairs_D", "./Assets/Models/FantasyDungeon/Textures/Stairs/Stairs_D.TGA");
	resources->loadTexture("Stairs_N", "./Assets/Models/FantasyDungeon/Textures/Stairs/Stairs_N.TGA");
	resources->loadTexture("Stairs_SRM", "./Assets/Models/FantasyDungeon/Textures/Stairs/Stairs_SRM.TGA");

	// Wall
	resources->loadModel("Niche", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/Niche.FBX");
	resources->getModel("Niche")->materialNames.push_back("Stairs");
	resources->getModel("Niche")->materialNames.push_back("brick2");
	resources->loadModel("Wall01", MESH_ATTRIBUTE_INSTANCE, "./Assets/Models/FantasyDungeon/Meshes/Wall/Wall01.FBX");
	resources->getModel("Wall01")->materialNames.push_back("brick2");
	resources->loadModel("Wall08", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/Wall08.FBX");
	resources->getModel("Wall08")->materialNames.push_back("brick2");
	resources->loadModel("wall09", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/wall09.FBX");
	resources->getModel("wall09")->materialNames.push_back("brick2");
	resources->loadModel("wall01Arch1", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/wall01Arch1.FBX");
	resources->getModel("wall01Arch1")->materialNames.push_back("brick2");
	resources->loadModel("WallDamaged02", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/WallDamaged02.FBX");
	resources->getModel("WallDamaged02")->materialNames.push_back("BrickDamege");
	resources->loadModel("WallDamaged03", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/WallDamaged03.FBX");
	resources->getModel("WallDamaged03")->materialNames.push_back("BrickDamege");
	resources->loadModel("Windows", MESH_ATTRIBUTE_DEFAULT, "./Assets/Models/FantasyDungeon/Meshes/Wall/Windows.FBX");
	resources->getModel("Windows")->materialNames.push_back("Sink");
	resources->getModel("Windows")->materialNames.push_back("Jail");
	resources->loadTexture("brick1_D", "./Assets/Models/FantasyDungeon/Textures/Wall/brick1_D.TGA");
	resources->loadTexture("brick1_N", "./Assets/Models/FantasyDungeon/Textures/Wall/brick1_N.TGA");
	resources->loadTexture("brick1_SRM", "./Assets/Models/FantasyDungeon/Textures/Wall/brick1_SRM.TGA");
	resources->loadTexture("brick2_D", "./Assets/Models/FantasyDungeon/Textures/Wall/brick2_D.TGA");
	resources->loadTexture("brick2_N", "./Assets/Models/FantasyDungeon/Textures/Wall/brick2_N.TGA");
	resources->loadTexture("brick2_SRM", "./Assets/Models/FantasyDungeon/Textures/Wall/brick2_SRM.TGA");
	resources->loadTexture("Brick4_D", "./Assets/Models/FantasyDungeon/Textures/Wall/Brick4_D.TGA");
	resources->loadTexture("Brick4_N", "./Assets/Models/FantasyDungeon/Textures/Wall/Brick4_N.TGA");
	resources->loadTexture("Brick4_SRM", "./Assets/Models/FantasyDungeon/Textures/Wall/Brick4_SRM.TGA");

	// Materials
	// Arch
	resources->createMaterial("Arch", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Arch")->addTexture("albedoMap", resources->getTexture("Arch_D"));
	resources->getMaterial("Arch")->addTexture("normalMap", resources->getTexture("Arch_N"));
	resources->getMaterial("Arch")->addTexture("maskMap", resources->getTexture("Brick4_SRM"));
	// Chandelier
	resources->createMaterial("Chandelier", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Chandelier")->addTexture("albedoMap", resources->getTexture("chandelier_D"));
	resources->getMaterial("Chandelier")->addTexture("normalMap", resources->getTexture("chandelier_N"));
	resources->getMaterial("Chandelier")->addTexture("maskMap", resources->getTexture("chandelier_SRM"));
	// BrickDamege
	resources->createMaterial("BrickDamege", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("BrickDamege")->addTexture("albedoMap", resources->getTexture("BrickDamage_D"));
	resources->getMaterial("BrickDamege")->addTexture("normalMap", resources->getTexture("BrickDamage_N"));
	resources->getMaterial("BrickDamege")->addTexture("maskMap", resources->getTexture("BrickDamage_SRM"));
	// brick1
	resources->createMaterial("brick1", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("brick1")->addTexture("albedoMap", resources->getTexture("brick1_D"));
	resources->getMaterial("brick1")->addTexture("normalMap", resources->getTexture("brick1_N"));
	resources->getMaterial("brick1")->addTexture("maskMap", resources->getTexture("brick1_SRM"));
	// brick2
	resources->createMaterial("brick2", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("brick2")->addTexture("albedoMap", resources->getTexture("brick2_D"));
	resources->getMaterial("brick2")->addTexture("normalMap", resources->getTexture("brick2_N"));
	resources->getMaterial("brick2")->addTexture("maskMap", resources->getTexture("brick2_SRM"));
	// column
	resources->createMaterial("column", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("column")->addTexture("albedoMap", resources->getTexture("Column_D"));
	resources->getMaterial("column")->addTexture("normalMap", resources->getTexture("Column_N"));
	resources->getMaterial("column")->addTexture("maskMap", resources->getTexture("Column_SRM"));
	// column_damage
	resources->createMaterial("column_damage", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("column_damage")->addTexture("albedoMap", resources->getTexture("Column_damage_D"));
	resources->getMaterial("column_damage")->addTexture("normalMap", resources->getTexture("Column_damage_N"));
	resources->getMaterial("column_damage")->addTexture("maskMap", resources->getTexture("Brick4_SRM"));
	// curbstone
	resources->createMaterial("curbstone", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("curbstone")->addTexture("albedoMap", resources->getTexture("curbstone_D"));
	resources->getMaterial("curbstone")->addTexture("normalMap", resources->getTexture("curbstone_N"));
	resources->getMaterial("curbstone")->addTexture("maskMap", resources->getTexture("curbstone_SRM"));
	// Door1
	resources->createMaterial("Door1", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Door1")->addTexture("albedoMap", resources->getTexture("Door1_D"));
	resources->getMaterial("Door1")->addTexture("normalMap", resources->getTexture("Door1_N"));
	resources->getMaterial("Door1")->addTexture("maskMap", resources->getTexture("Door1_SRM"));
	// DoorArch
	resources->createMaterial("DoorArch", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("DoorArch")->addTexture("albedoMap", resources->getTexture("DoorArch_D"));
	resources->getMaterial("DoorArch")->addTexture("normalMap", resources->getTexture("DoorArch_N"));
	resources->getMaterial("DoorArch")->addTexture("maskMap", resources->getTexture("DoorArch_SRM"));
	// Jail
	resources->createMaterial("Jail", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Jail")->addTexture("albedoMap", resources->getTexture("Jail_D"));
	resources->getMaterial("Jail")->addTexture("normalMap", resources->getTexture("Jail_N"));
	resources->getMaterial("Jail")->addTexture("maskMap", resources->getTexture("Jail_SRM"));
	// pavement1
	resources->createMaterial("pavement1", resources->getShader("FantasyDungeonWet"));
	resources->getMaterial("pavement1")->addTexture("albedoMap", resources->getTexture("pavement1_D"));
	resources->getMaterial("pavement1")->addTexture("normalMap", resources->getTexture("pavement1_N"));
	resources->getMaterial("pavement1")->addTexture("maskMap", resources->getTexture("pavement1_SRM"));
	resources->getMaterial("pavement1")->addTexture("factorMap", resources->getTexture("Mask1"));
	// pavement2
	resources->createMaterial("pavement2", resources->getShader("FantasyDungeonWet"));
	resources->getMaterial("pavement2")->addTexture("albedoMap", resources->getTexture("pavement2_D"));
	resources->getMaterial("pavement2")->addTexture("normalMap", resources->getTexture("pavement2_N"));
	resources->getMaterial("pavement2")->addTexture("maskMap", resources->getTexture("pavement2_SRM"));
	resources->getMaterial("pavement2")->addTexture("factorMap", resources->getTexture("Mask1"));
	// Railing
	resources->createMaterial("Railing", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Railing")->addTexture("albedoMap", resources->getTexture("Railing_D"));
	resources->getMaterial("Railing")->addTexture("normalMap", resources->getTexture("Railing_N"));
	resources->getMaterial("Railing")->addTexture("maskMap", resources->getTexture("Brick4_SRM"));
	// Roof
	resources->createMaterial("Roof", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Roof")->addTexture("albedoMap", resources->getTexture("Roof_D"));
	resources->getMaterial("Roof")->addTexture("normalMap", resources->getTexture("Roof_N"));
	resources->getMaterial("Roof")->addTexture("maskMap", resources->getTexture("Brick4_SRM"));
	// Sink
	resources->createMaterial("Sink", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Sink")->addTexture("albedoMap", resources->getTexture("Sink_D"));
	resources->getMaterial("Sink")->addTexture("normalMap", resources->getTexture("Sink_N"));
	resources->getMaterial("Sink")->addTexture("maskMap", resources->getTexture("Sink_SRM"));
	// Stairs
	resources->createMaterial("Stairs", resources->getShader("FantasyDungeonSRM"));
	resources->getMaterial("Stairs")->addTexture("albedoMap", resources->getTexture("Stairs_D"));
	resources->getMaterial("Stairs")->addTexture("normalMap", resources->getTexture("Stairs_N"));
	resources->getMaterial("Stairs")->addTexture("maskMap", resources->getTexture("Stairs_SRM"));


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
	MeshRenderer* playerMeshRenderer = player->addComponent<MeshRenderer>();
	playerMeshRenderer->model = game->resources->getModel("player");
	playerMeshRenderer->materials.push_back(game->resources->getMaterial("player"));
	playerMeshRenderer->castShadow = true;
	this->addGameObject("player", player);
	game->shadowMapping->target = player;

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

	Map* map = new Map(this, "./Assets/Models/FantasyDungeon/Maps/Map2.fbx");
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
		// MeshRenderer* lightMeshRenderer = light[i]->addComponent<MeshRenderer>();
		// lightMeshRenderer->model = game->resources->getModel("sphere");
		// lightMeshRenderer->materials.push_back(game->resources->getMaterial("simple"));
		this->addGameObject(("light" + std::to_string(i)).c_str(), light[i]);
	}
	light[0]->getComponent<Transform>()->position = glm::vec3(0, 2.5, -5);
	light[1]->getComponent<Transform>()->position = glm::vec3(0, 2.5, 0);
	light[2]->getComponent<Transform>()->position = glm::vec3(0, 5, -15);
	light[3]->getComponent<Transform>()->position = glm::vec3(0, 7.5, -25);
	light[0]->getComponent<PointLight>()->color = glm::vec3(2, 4, 5);
	light[0]->getComponent<PointLight>()->intensity = 5;
	light[1]->getComponent<PointLight>()->color = glm::vec3(1, 1, 1);
	light[1]->getComponent<PointLight>()->intensity = 5;
	light[2]->getComponent<PointLight>()->color = glm::vec3(2, 4, 5);
	light[2]->getComponent<PointLight>()->intensity = 5;
	light[3]->getComponent<PointLight>()->color = glm::vec3(2, 4, 5);
	light[3]->getComponent<PointLight>()->intensity = 5;

}

