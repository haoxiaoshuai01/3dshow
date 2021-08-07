#include "CObject.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"

CObject::CObject()
{
	postion = glm::vec3(0.0f,0.0f,0.0f);
	R = glm::mat3(1.0f);
	S = glm::vec3(1.0f, 1.0f, 1.0f);
	updateMatrix();
}

void CObject::update()
{
	updateMatrix();
}

void CObject::Draw()
{
}

void CObject::updateMatrix()
{
	//glm:: col priority
	//glm::decompose();
	modelMatrix = glm::mat4(1.0f);
	////t
	modelMatrix[3][0] = postion[0];
	modelMatrix[3][1] = postion[1];
	modelMatrix[3][2] = postion[2];
	////r S
	modelMatrix[0][0] = R[0][0] * S[0];
	modelMatrix[0][1] = R[0][1];
	modelMatrix[0][2] = R[0][2];

	modelMatrix[1][0] = R[1][0] ;
	modelMatrix[1][1] = R[1][1] * S[1];
	modelMatrix[1][2] = R[1][2] ;

	modelMatrix[2][0] = R[2][0];
	modelMatrix[2][1] = R[2][1] ;
	modelMatrix[2][2] = R[2][2] * S[2];


}
