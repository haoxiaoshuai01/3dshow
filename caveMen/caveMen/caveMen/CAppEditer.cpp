#include "CAppEditer.h"
#include <GL/gl3w.h> 
#include <GLFW/glfw3.h>
//#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include "stb_image.h"

#include <iostream>
#include <imgui.h>



void CAppEditer::init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	stbi_set_flip_vertically_on_load(true);

	ourShader = new Shader("../../res/shader/1.model_loading.vs", "../../res/shader/1.model_loading.fs");

	// load models
	// -----------
	
	Model*p  = new Model("../../res/objects/backpack/backpack.obj");
	Model*p2 = new Model(*p);
	drawModel.push_back(p);
	drawModel.push_back(p2);
	//p->modelMatrix = glm::translate(p->modelMatrix, glm::vec3(5.0f, 0.0f, 0.0f));
}

CAppEditer::CAppEditer()
{
	init();
}

CAppEditer::~CAppEditer()
{
	
}

void CAppEditer::Load()
{
}

void CAppEditer::Unload()
{
}

void CAppEditer::Update()
{
	if (ImGui::IsKeyPressed(GLFW_KEY_W))
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (ImGui::IsKeyPressed(GLFW_KEY_S))
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (ImGui::IsKeyPressed(GLFW_KEY_A))
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (ImGui::IsKeyPressed(GLFW_KEY_D))
		camera->ProcessKeyboard(RIGHT, deltaTime);
}

void CAppEditer::Draw(int w,int h)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// don't forget to enable shader before setting uniforms
	ourShader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)w / (float)h, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);

	for (auto &itemModel : drawModel)
	{
		itemModel->modelMatrix = glm::translate(itemModel->modelMatrix, glm::vec3(5.0f, 0.0f, 0.0f));
		ourShader->setMat4("model", itemModel->modelMatrix);
		itemModel->Draw(*ourShader);
		break;
	}
}
