#pragma once
#include "learnopengl/shader_m.h"
#include "dataStruct.h"
#include "CObject.h"

class CArrowsAxis :public CObject
{
	public:
		CArrowsAxis(Eigen::Vector3f sourcePoint, Eigen::Vector3f endPoint, Shader* lineshader, glm::mat4 *project, glm::mat4 *lookat);
		// mesh Data
		std::vector<SVertex>       vertices;
		std::vector<unsigned int>  indices;
		unsigned int VAO;
		// render data 
		unsigned int VBO, EBO;

		void addVertices(Eigen::Vector3f sourcePoint, Eigen::Vector3f endPoint);
		// initializes all the buffer objects/arrays
		void setup();
		void Draw();
};

