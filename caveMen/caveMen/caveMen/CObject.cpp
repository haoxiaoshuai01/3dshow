#include "CObject.h"
#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include "glm/gtx/matrix_decompose.hpp"

#include <math.h>
unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
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
void CObject::genboundingbox(Eigen::Matrix<float, Eigen::Dynamic, 3> vertexs)
{
	boundingboxMin(0) = vertexs.col(0).minCoeff();
	boundingboxMin(1) = vertexs.col(1).minCoeff();
	boundingboxMin(2) = vertexs.col(2).minCoeff();

	boundingboxMax(0) = vertexs.col(0).maxCoeff();
	boundingboxMax(1) = vertexs.col(1).maxCoeff();
	boundingboxMax(2) = vertexs.col(2).maxCoeff();
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

