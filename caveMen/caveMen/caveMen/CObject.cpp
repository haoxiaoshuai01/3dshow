#include "CObject.h"
#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include "glm/gtx/matrix_decompose.hpp"

#include <math.h>

CObject::CObject()
{
	postion = glm::vec3(0.0f,0.0f,0.0f);
	R = Eigen::Matrix3f().Identity();
	S = glm::vec3(1.0f, 1.0f, 1.0f);
	eulerAngle = glm::vec3(0.0f,0.0f,0.0f);
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

	R = eulerAngle2RMatix(eulerAngle);

	////r S
	modelMatrix[0][0] = R(0,0) * S[0];
	modelMatrix[0][1] = R(1,0);
	modelMatrix[0][2] = R(2,0);

	modelMatrix[1][0] = R(0,1) ;
	modelMatrix[1][1] = R(1,1) * S[1];
	modelMatrix[1][2] = R(2,1);

	modelMatrix[2][0] = R(0, 2);
	modelMatrix[2][1] = R(1, 2);
	modelMatrix[2][2] = R(2, 2) * S[2];

}
/*slamʮ�Ľ����ᵽ�ĳ�����ת˳����Z-Y-X��
��Ӧrpy��ָ�ľ����������������ᣩZ-Y-X˳��
��ŷ����ת������ת�����������������ϵ����ת����ͨ���ǰ�������ʽ���ƹ̶��ᣩ��
��X-Y-Z˳��������ת����Ϊ��
[��ʽ]r = rz*ry*rx;
*/
Eigen::Matrix3f CObject::eulerAngle2RMatix(glm::vec3 e)
{
	Eigen::Vector3f rade(e.x*M_PI / 180.0f, e.y*M_PI / 180.0f, e.z*M_PI / 180.0f);
	Eigen::AngleAxisf rotation_vector(rade(2), Eigen::Vector3f(0, 0, 1));
	Eigen::AngleAxisf rotation_vector2(rade(1), Eigen::Vector3f(0, 1, 0));
	Eigen::AngleAxisf rotation_vector3(rade(0), Eigen::Vector3f(1, 0, 0));
	return rotation_vector.matrix() * rotation_vector2.matrix() *rotation_vector3.matrix();
}

