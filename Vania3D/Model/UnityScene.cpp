
#include "Engine.hpp"


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
UnityScene::UnityScene() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
UnityScene::~UnityScene() {

}


/*------------------------------------------------------------------------------
< load >
------------------------------------------------------------------------------*/
void UnityScene::load(const char* path) {

	FILE* file = fopen(path, "rb");
	if (file == nullptr) {
		printf("[loadObj] impossible to open: <%s>\n", path);
		return;
	}
	
	// data
	unsigned int classID, fileID;
	
	// check header
	char lineHeader[128], restOfLine[1024];
	
	while (true) {
		// read the first word of the line
		if (fscanf(file, "%s", lineHeader) == EOF) break;
		
		// parse lineHeader
		if (strcmp(lineHeader, "---") == 0) {
			fscanf(file, " !u!%u &%u", &classID, &fileID);
			// GameObject
			if (classID == 1) {
				this->unitySceneDatas.insert(std::make_pair(fileID, new UnitySceneData()));
				while (strcmp(lineHeader, "m_Name:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fscanf(file, " %s", this->unitySceneDatas[fileID]->name);
			}
			// Transform
			if (classID == 4) {
				while (strcmp(lineHeader, "m_GameObject:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fscanf(file, " {fileID: %u}", &fileID);
				
				while (strcmp(lineHeader, "m_LocalRotation:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fscanf(file, " {x: %f, y: %f, z: %f, w: %f}", &this->unitySceneDatas[fileID]->rotation.x, &this->unitySceneDatas[fileID]->rotation.y, &this->unitySceneDatas[fileID]->rotation.z, &this->unitySceneDatas[fileID]->rotation.w);
				
				while (strcmp(lineHeader, "m_LocalPosition:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fscanf(file, " {x: %f, y: %f, z: %f}", &this->unitySceneDatas[fileID]->position.x, &this->unitySceneDatas[fileID]->position.y, &this->unitySceneDatas[fileID]->position.z);
				
				while (strcmp(lineHeader, "m_LocalScale:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fscanf(file, " {x: %f, y: %f, z: %f}", &this->unitySceneDatas[fileID]->scale.x, &this->unitySceneDatas[fileID]->scale.y, &this->unitySceneDatas[fileID]->scale.z);
				
				while (strcmp(lineHeader, "m_Children:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fgets(restOfLine, 1024, file); // eat up the rest of the line
				fscanf(file, "%s", lineHeader);
				while (strcmp(lineHeader, "-") == 0) {
					unsigned int childrenID;
					fscanf(file, " {fileID: %u}", &childrenID);
					this->unitySceneDatas[fileID]->childrenIDs.push_back(childrenID);
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				
				while (strcmp(lineHeader, "m_Father:") != 0) {
					fgets(restOfLine, 1024, file); // eat up the rest of the line
					fscanf(file, "%s", lineHeader);
				}
				fscanf(file, " {fileID: %u}", &this->unitySceneDatas[fileID]->parentID);
			}
		}
		else {
			fgets(restOfLine, 1024, file); // eat up the rest of the line
		}
	}
	
	// close OBJ file
	fclose(file);

}
