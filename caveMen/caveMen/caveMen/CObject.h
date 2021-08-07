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
	virtual void update();
	virtual void Draw();
	glm::mat4 modelMatrix;
	void updateMatrix();
	glm::vec3 postion;
	glm::mat3 R;
	glm::vec3 S;
	bool flagUpdateActived = false;
};

