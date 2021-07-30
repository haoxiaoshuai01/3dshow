#pragma once
#include "CObject.h"
#include "dataStruct.h"
class CLine :
	public CObject
{
public:
	CLine(glm::vec2 startv,glm::vec2 endv);
	// mesh Data
	std::vector<SVertex>       vertices;
	std::vector<unsigned int>  indices;

	void updateVertex();
	void Draw();
	unsigned int VAO;
	// render data 
	unsigned int VBO, EBO;
	float z = 3.01f;
	glm::vec2 start;
	glm::vec2 endP;
	float Lwidth = 0.05f;
};

