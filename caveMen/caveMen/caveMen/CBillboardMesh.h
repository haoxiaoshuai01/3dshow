#pragma once
#include "CObject.h"
#include "dataStruct.h"
#include "CAppEditer.h"
class CBillboardMesh :
	public CObject
{
public:
	CBillboardMesh(std::vector<SVertex> vertices, std::vector<unsigned int> indices);
	void Draw();

	// mesh Data
	std::vector<SVertex>       vertices;
	std::vector<unsigned int>  indices;
	unsigned int VAO;
	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
};

