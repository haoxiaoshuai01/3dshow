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
#include <iostream>
#include <vector>

enum class EActorType
{
	eNone = 0,
	eModel,
	eLine,
	eSeleAixs,
	eGlobalAixs,
	eMesh
};
class CObject
{
public:
	CObject();
	virtual void update();
	virtual void Draw();
	glm::mat4 modelMatrix;
	void updateMatrix();
	void genboundingbox(Eigen::Matrix<float, Eigen::Dynamic,3> vertexs);
	Eigen::Matrix3f eulerAngle2RMatix(glm::vec3 e);
	glm::vec3 postion;
	Eigen::Matrix3f R;
	//glm::vec4 quaternion;
	glm::vec3 eulerAngle;
	glm::vec3 S;
	bool flagUpdateActived = false;
	Eigen::Vector3f boundingboxMin;
	Eigen::Vector3f boundingboxMax;
	bool isHide = false;
	EActorType actorType;
	bool isSelected = false;
};

