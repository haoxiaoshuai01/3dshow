#include "CAppEditer.h"
#include <GL/gl3w.h> 
#include <GLFW/glfw3.h>
//#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include "stb_image.h"
#include "CMesh.h"
#include <iostream>
#include <imgui.h>
#include "CLIne.h"

using namespace glm;


void CAppEditer::init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 20.0f));
	stbi_set_flip_vertically_on_load(true);

	modelShader = new Shader("../../res/shader/1.model_loading.vs", "../../res/shader/1.model_loading.fs");
	meshShader = new Shader("../../res/shader/cmesh_shader.vs", "../../res/shader/cmesh_shader.fs");
	// load models
	// -----------
	//addModel();
	
	
	addLine();
	addMesh();
}

CAppEditer::CAppEditer()
{
	
}

CAppEditer::~CAppEditer()
{
	
}

void CAppEditer::addMesh()
{
	std::vector<SVertex> vertexVectors;
	vertexVectors.push_back(SVertex(vec3(10, 10, 3), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(10, -10, 3), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-10, -10, 3), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-10, 10, 3), vec3(0.5, 0.5, 0.5)));
	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	CMesh *mesh = new CMesh(vertexVectors, indices);
	drawMesh.push_back(mesh);
	
}

void CAppEditer::addLine()
{
	CLine *line = new CLine(vec2(0, -10), vec2(0, 10));
	drawLine.push_back(line);
	line = new CLine(vec2(-10, 0), vec2(10, 0));
	drawLine.push_back(line);

	/*line = new CLine(vec2(0, 0), vec2(10, 10));
	drawLine.push_back(line);
	line = new CLine(vec2(0, 0), vec2(-10, 10));
	drawLine.push_back(line);*/
}

void CAppEditer::addModel()
{
	Model*p = new Model("../../res/objects/backpack/backpack.obj");
	Model*p2 = new Model(*p);
	drawModel.push_back(p);
	drawModel.push_back(p2);
	p->modelMatrix = glm::translate(p->modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	p2->modelMatrix = glm::translate(p2->modelMatrix, glm::vec3(3.0f, 0.0f, 0.0f));
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
	if (ImGui::IsKeyPressed(GLFW_KEY_Q))
		camera->ProcessKeyboard(Down, deltaTime);
	if (ImGui::IsKeyPressed(GLFW_KEY_E))
		camera->ProcessKeyboard(UP, deltaTime);


	static  ImVec2 lastPos;

	if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
	{
		float xoffset = ImGui::GetMousePos().x - lastPos.x;
		float yoffset = lastPos.y - ImGui::GetMousePos().y;

		camera->ProcessMouseMovement(xoffset, yoffset);
	}
	lastPos = ImGui::GetMousePos();
	//std::cout << "deltaTime %" << deltaTime<<"\n";
}

void CAppEditer::Draw()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// don't forget to enable shader before setting uniforms
	modelShader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)windowsW / (float)windowsH, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	modelShader->setMat4("projection", projection);
	modelShader->setMat4("view", view);

	for (auto &itemModel : drawModel)
	{
		modelShader->setMat4("model", itemModel->modelMatrix);
		itemModel->Draw(*modelShader);
	}

	meshShader->use();
	meshShader->setMat4("projection", projection);
	meshShader->setMat4("view", view);

	for (auto &itemMesh : drawMesh)
	{
		meshShader->setMat4("model", itemMesh->modelMatrix);
		itemMesh->Draw();
	}

	for (auto &itemline : drawLine)
	{
		meshShader->setMat4("model", itemline->modelMatrix);
		itemline->Draw();
	}
	
}
