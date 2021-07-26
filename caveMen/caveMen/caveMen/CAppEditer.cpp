#include "CAppEditer.h"
#include <GL/gl3w.h> 
//#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include "stb_image.h"

#include <iostream>


void CAppEditer::init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glEnable(GL_DEPTH_TEST);
	stbi_set_flip_vertically_on_load(true);

	ourShader = new Shader("../../res/shader/1.model_loading.vs", "../../res/shader/1.model_loading.fs");

	// load models
	// -----------
	ourModel = new Model("../../res/objects/backpack/backpack.obj");
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
}

void CAppEditer::Draw()
{

	// don't forget to enable shader before setting uniforms
	ourShader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom),
		(float)1280 / (float)720, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
   // model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	ourShader->setMat4("model", model);
	ourModel->Draw(*ourShader);


}
