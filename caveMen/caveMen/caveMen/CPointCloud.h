#pragma once
#include "CObject.h"
#include "dataStruct.h"
class CPointCloud :
	public CObject
{
public:
	CPointCloud(std::vector<glm::vec2>  postions);
	void updateVectorCloud();
	void Draw();
	
	float z = 3.01f;
	//// mesh Data
	std::vector<SVertex>       vertices;
	std::vector<unsigned int>  indices;
	unsigned int VAO;
	//render data
	unsigned int VBO,EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
};

