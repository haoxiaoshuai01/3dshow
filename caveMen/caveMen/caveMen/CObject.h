#pragma once
#include <GL/gl3w.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Eigen/Core"
#include <Eigen/Geometry>
class CObject
{
	
public:
	CObject();
	virtual void update();
	virtual void Draw();
	glm::mat4 modelMatrix;
	void updateMatrix();
	Eigen::Matrix3f eulerAngle2RMatix(glm::vec3 e);
	glm::vec3 postion;
	Eigen::Matrix3f R;
	//glm::vec4 quaternion;
	glm::vec3 eulerAngle;
	glm::vec3 S;
	bool flagUpdateActived = false;
};

