#pragma once
#include "CObject.h"
class CPointCloud :
	public CObject
{
public:
	CPointCloud();
	void updateVectorCloud();
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

