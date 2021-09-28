#pragma once

#include <vector>
#include "CAppEditer.h"
class CShowScreenMesh
{
public:
	struct DataV
	{
		DataV(glm::vec2 p , glm::vec2 t) 
		{
			Position = p;
			TexCoords = t;
		}
		glm::vec2 Position;
		glm::vec2 TexCoords;
	};

	CShowScreenMesh(unsigned int *screenTexture_);
	void Draw();

	// mesh Data
	std::vector<DataV>       vertices;
	std::vector<unsigned int>  indices;
	unsigned int VAO;
	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
	unsigned int *screenTexture;

private:
	

};

