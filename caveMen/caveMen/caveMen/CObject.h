#pragma once
#include <GL/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class CObject
{
	
public:
	CObject();
	glm::mat4 modelMatrix;
	glm::vec3 postion;
};

