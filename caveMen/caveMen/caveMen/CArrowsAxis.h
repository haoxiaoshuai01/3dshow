#pragma once
#include "learnopengl/shader_m.h"
#include "dataStruct.h"
#include "CObject.h"
enum class ESeleArrowsType
{
	eNone,
	eXArrow,
	eYArrow,
	eZArrow
};

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
		glm::vec4 color;
		glm::mat4 *mproject;
		glm::mat4 *mlookat;
		Shader *mlineshader;
		CObject *model =nullptr;
		bool DrawAlwaydepthTest = true;
		ESeleArrowsType mseleArrowsType;
};

