#pragma once
#include "CObject.h"
#include "dataStruct.h"
#include "learnopengl/shader_m.h"
class CSkybox :public CObject
{
public:
	CSkybox(Shader*skyboxShader,glm::mat4 *pro, glm::mat4 *view);
	~CSkybox();
	std::vector<vec3>       vertices;

	void Draw();
	unsigned int VAO;
	// render data 
	unsigned int VBO;
	Shader *mSkyboxShader;
	glm::mat4 *mPro;
	glm::mat4 *mView;
	unsigned int cubemapTexture;
};

