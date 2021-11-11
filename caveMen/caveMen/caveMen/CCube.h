#pragma once
#include "CObject.h"
#include "dataStruct.h"

class CCube :public CObject
{
public:
	CCube(glm::mat4 *pro, glm::mat4 *view,Shader *shader);
	void Draw();

	// mesh Data
	std::vector<SVertex>       vertices;
	std::vector<unsigned int>  indices;
	unsigned int VAO;
	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
	glm::mat4 *mpro;
	glm::mat4 *mview;
	Shader * mshader;

	bool isActivedMove = false;
	vec3 beginPosition;
	vec3 endPosition;
};

