
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "Engine.hpp"

/*------------------------------------------------------------------------------
< convert from Assimp to glm >
------------------------------------------------------------------------------*/
glm::vec2 assignment(const aiVector2D& assimpVector) {
	return glm::vec2(assimpVector.x, assimpVector.y);
}

glm::vec3 assignment(const aiVector3D& assimpVector) {
	return glm::vec3(assimpVector.x, assimpVector.y, assimpVector.z);
}

glm::vec3 assignment(const aiColor3D& assimpColor) {
	return glm::vec3(assimpColor.r, assimpColor.g, assimpColor.b);
}

glm::quat assignment(const aiQuaternion& assimpQuaternion) {
	return glm::quat(assimpQuaternion.w, assimpQuaternion.x, assimpQuaternion.y, assimpQuaternion.z);
}

glm::mat4 assignment(const aiMatrix4x4& assimpMatrix) {
	glm::mat4 result = {
		assimpMatrix.a1, assimpMatrix.b1, assimpMatrix.c1, assimpMatrix.d1,
		assimpMatrix.a2, assimpMatrix.b2, assimpMatrix.c2, assimpMatrix.d2,
		assimpMatrix.a3, assimpMatrix.b3, assimpMatrix.c3, assimpMatrix.d3,
		assimpMatrix.a4, assimpMatrix.b4, assimpMatrix.c4, assimpMatrix.d4
	};
	return result;
}

glm::mat4 assignment(const aiMatrix3x3& assimpMatrix) {
	glm::mat4 result = {
		assimpMatrix.a1, assimpMatrix.b1, assimpMatrix.c1, 0.0,
		assimpMatrix.a2, assimpMatrix.b2, assimpMatrix.c2, 0.0,
		assimpMatrix.a3, assimpMatrix.b3, assimpMatrix.c3, 0.0,
		            0.0,             0.0,             0.0, 1.0
	};
	return result;
}
