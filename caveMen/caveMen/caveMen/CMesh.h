#pragma once
#include "CObject.h"
#include "dataStruct.h"



class CMesh :
	public CObject
{
public: 
	CMesh(std::vector<SVertex> vertices, std::vector<unsigned int> indices );
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

