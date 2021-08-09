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
#include "CPointCloud.h"
#include "geometry.h"
#include "testdata.h"

#include <time.h>
#include <chrono>  
#include <iostream> 

using namespace glm;
time_t getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//获取当前时间点
	time_t timestamp = tp.time_since_epoch().count(); //计算距离1970-1-1,00:00的时间长度
	return timestamp;
}


void CAppEditer::init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 20.0f));
	stbi_set_flip_vertically_on_load(true);

	modelShader = new Shader("../../res/shader/1.model_loading.vs", "../../res/shader/1.model_loading.fs");
	meshShader = new Shader("../../res/shader/cmesh_shader.vs", "../../res/shader/cmesh_shader.fs");
	lineShader = new Shader("../../res/shader/line.vs", "../../res/shader/line.fs");
	// load models
	// -----------
	addModel();
	
	addLine();
	addMesh();
	addPoint();
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
	vertexVectors.push_back(SVertex(vec3(-5.0f, -5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, -5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, 5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, 5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));

	vertexVectors.push_back(SVertex(vec3(-5.0f, -5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, -5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, 5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, 5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));

	vertexVectors.push_back(SVertex(vec3(-5.0f, 5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, 5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, -5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, -5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));

	vertexVectors.push_back(SVertex(vec3(5.0f, 5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, 5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, -5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, -5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));

	vertexVectors.push_back(SVertex(vec3(-5.0f, -5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, -5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, -5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, -5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));

	vertexVectors.push_back(SVertex(vec3(-5.0f, 5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, 5.0f, -5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(5.0f, 5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));
	vertexVectors.push_back(SVertex(vec3(-5.0f, 5.0f, 5.0f), vec3(0.5, 0.5, 0.5)));


	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(0+4);
	indices.push_back(1+4);
	indices.push_back(3+4);
	indices.push_back(1+4);
	indices.push_back(2+4);
	indices.push_back(3+4);

	indices.push_back(0+8);
	indices.push_back(1+8);
	indices.push_back(3+8);
	indices.push_back(1+8);
	indices.push_back(2+8);
	indices.push_back(3+8);

	indices.push_back(0+12);
	indices.push_back(1+12);
	indices.push_back(3+12);
	indices.push_back(1+12);
	indices.push_back(2+12);
	indices.push_back(3+12);

	indices.push_back(0+16);
	indices.push_back(1+16);
	indices.push_back(3+16);
	indices.push_back(1+16);
	indices.push_back(2+16);
	indices.push_back(3+16);

	indices.push_back(0+20);
	indices.push_back(1+20);
	indices.push_back(3+20);
	indices.push_back(1+20);
	indices.push_back(2+20);
	indices.push_back(3+20);

	CMesh *mesh = new CMesh(vertexVectors, indices);
	drawMesh.push_back(mesh);
	mesh->postion = vec3(10.0f, 0.0f, 0.0f);
	mesh->update();
}

void CAppEditer::addLine()
{
	CLine *line = new CLine(vec2(0, -10), vec2(0, 10));
	drawLine.push_back(line);
	CLine *line2 = new CLine(vec2(-10, 0), vec2(10, 0));
	drawLine.push_back(line2);

	CLinewidth1 *linwidth1 = new CLinewidth1(vec3(-10,0,4),vec3(10,0,4));
	drawLineWidth1s.push_back(linwidth1);

}

void CAppEditer::addModel()
{
	Model*p = new Model("../../res/objects/backpack/backpack.obj");
	Eigen::Vector3f min_=  p->boundingboxMin;
	Eigen::Vector3f max_= p->boundingboxMax;
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), min_(1), min_(2)), vec3(max_(0), min_(1), min_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), min_(1), min_(2)), vec3(min_(0), max_(1), min_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), max_(1), min_(2)), vec3(max_(0), max_(1), min_(2))));

	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), min_(2)), vec3(max_(0), min_(1), min_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), min_(1), min_(2)), vec3(min_(0), min_(1), max_(2))));

	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), max_(2)), vec3(max_(0), max_(1), min_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), max_(2)), vec3(min_(0), max_(1), max_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), max_(1), max_(2)), vec3(max_(0), min_(1), max_(2))));

	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), min_(1), max_(2)), vec3(min_(0), min_(1), max_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), max_(1), max_(2)), vec3(min_(0), min_(1), max_(2))));

	drawLineWidth1s.push_back(new CLinewidth1(vec3(max_(0), min_(1), max_(2)), vec3(max_(0), min_(1), min_(2))));
	drawLineWidth1s.push_back(new CLinewidth1(vec3(min_(0), max_(1), max_(2)), vec3(min_(0), max_(1), min_(2))));



	Model*p2 = new Model(*p);
	drawModel.push_back(p);
	drawModel.push_back(p2);
	p2->postion = glm::vec3(-5.0f, 0.0f, 0.0f);
	p2->S = vec3(0.5f, 1.0f, 0.5f);
	p2->eulerAngle = vec3(0.0f, 0.0f,45.0f );
	p2->update();
}

void CAppEditer::addPoint()
{
	std::vector<glm::vec2> poss;
	poss.push_back({ 2,2 });
	poss.push_back({ 3,3 });
	poss.push_back({ 4,4 });
	poss.push_back({ 5,5 });
	pointCould = new CPointCloud(poss);
}

void CAppEditer::Load()
{
}

void CAppEditer::Unload()
{
}

void CAppEditer::Update()
{
	ImGuiIO& io = ImGui::GetIO();

	if (io.KeysDown[GLFW_KEY_W])
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (io.KeysDown[GLFW_KEY_S])
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (io.KeysDown[GLFW_KEY_A])
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (io.KeysDown[GLFW_KEY_D])
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (io.KeysDown[GLFW_KEY_Q])
		camera->ProcessKeyboard(Down, deltaTime);
	if (io.KeysDown[GLFW_KEY_E])
		camera->ProcessKeyboard(UP, deltaTime);

	static  ImVec2 lastPos;

	if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
	{
		float xoffset = ImGui::GetMousePos().x - lastPos.x;
		float yoffset = lastPos.y - ImGui::GetMousePos().y;

		camera->ProcessMouseMovement(xoffset, yoffset);
	}
	lastPos = ImGui::GetMousePos();
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		glm::vec3 posWorld =  getScreenWordPos({ ImGui::GetMousePos().x, ImGui::GetMousePos().y });
		
		CLinewidth1 *line = new CLinewidth1(vec3(camera->Position.x, camera->Position.y, camera->Position.z), posWorld);
		drawLineWidth1s.push_back(line);
		//vec3(camera->Position.x, camera->Position.y, camera->Position.z),
		float v = glm::dot(vec2(1, 0), vec2(0, 1));
		
		
		for (auto item:Testdata:: rayINDatas)
		{
			bool isintersect = Geomery::intersectRayPolygon(item.o,item.dir,item.point1,item.point2,item.point3);
			int i = 0;
		}

	}

}

void CAppEditer::Draw()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//std::cout << deltaTime;
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// don't forget to enable shader before setting uniforms
	modelShader->use();

	// view/projection transformations
	projection = glm::perspective(glm::radians(camera->Zoom), (float)windowsW / (float)windowsH, 0.1f, 100.0f);
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

	//meshShader->setMat4("model", pointCould->modelMatrix);
	//pointCould->Draw();

	lineShader->use();
	lineShader->setMat4("projection", projection);
	lineShader->setMat4("view", view);
	for (auto &itemline : drawLineWidth1s)
	{
		lineShader->setMat4("model", itemline->modelMatrix);
		itemline->Draw();
	}
	
}

glm::vec3 CAppEditer::getScreenWordPos(glm::vec2 pos)
{

	float x = (2.0f * pos.x) / windowsW - 1.0f;
	float y = 1.0f - (2.0f * pos.y / windowsH);
	float z = 1.0f;
	vec3 ray_nds = vec3(x, y, z);
	vec4 ray_clip = vec4(ray_nds.x, ray_nds.y, ray_nds.z, 1.0);
	vec4 ray_eye = glm::inverse(projection) * ray_clip;
	vec4 ray_world = glm::inverse(camera->GetViewMatrix()) * ray_eye;
	vec3 xyz;
	if (ray_world.w != 0.0)
	{
		xyz.x= ray_world.x /ray_world.w;
		xyz.y= ray_world.y /ray_world.w;
		xyz.z= ray_world.z /ray_world.w;
	}

	return xyz;	
}
