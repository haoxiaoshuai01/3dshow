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
#include "boost/thread.hpp"
#include "CSkybox.h"
#include "CCube.h"
#include "C3DViewPortWidget.h"

using namespace glm;
time_t getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//��ȡ��ǰʱ���
	time_t timestamp = tp.time_since_epoch().count(); //�������1970-1-1,00:00��ʱ�䳤��
	return timestamp;
}


void CAppEditer::init()
{
	view3dwidget = new C3DViewPortWidget();
	camera = new Camera(glm::vec3(0.0f, 3.0f, 20.0f));
	

	modelShader = new Shader("../../res/shader/1.model_loading.vs", "../../res/shader/1.model_loading.fs");
	meshShader = new Shader("../../res/shader/cmesh_shader.vs", "../../res/shader/cmesh_shader.fs");
	lineShader = new Shader("../../res/shader/line.vs", "../../res/shader/line.fs");
	skyboxShader = new Shader("../../res/shader/skybox.vs", "../../res/shader/skybox.fs");
	
	
	// load models
	// -----------
	addSkyBox();
	stbi_set_flip_vertically_on_load(true);
	addModel();
	addGridLine();
	addAxis();
	addCube();

	//������ ͨ����Ȳ��� ��Զ��ǰ��
	addseleAxis();
}

CAppEditer::CAppEditer()
{
	
}

CAppEditer::~CAppEditer()
{
	
}

void CAppEditer::addMesh()
{
	
	/*std::vector<SVertex> v;
	v.push_back(SVertex(vec3(-10.0f, 10.0f, 3.0f), vec3(0.5, 0.6, 0.5)));
	v.push_back(SVertex(vec3(10.0f, 10.0f, 3.0f), vec3(0.5, 0.6, 0.5)));
	v.push_back(SVertex(vec3(10.0f, -10.0f, 3.0f), vec3(0.5, 0.6, 0.5)));
	v.push_back(SVertex(vec3(-10.0f, -10.0f, 3.0f), vec3(0.5, 0.6, 0.5)));
	std::vector<unsigned int> indices_;
	indices_.push_back(0);
	indices_.push_back(1);
	indices_.push_back(3);
	indices_.push_back(1);
	indices_.push_back(2);
	indices_.push_back(3);
	drawMesh.push_back(new CMesh(v, indices));*/
}

void CAppEditer::addSkyBox()
{
	
	CSkybox *box = new CSkybox(skyboxShader, &projection, &view);
	drawObject.insert(drawObject.begin(), box);

}

void CAppEditer::addGridLine()
{
	for (int i = -50; i < 51; i++)
	{
		CLinewidth1 *linwidth1 = new CLinewidth1(vec3(-50, 0, (float)i), vec3(50,0, (float)i),lineShader,&projection,&view);
		drawObject.push_back(linwidth1);
		CLinewidth1 *linwidth2 = new CLinewidth1(vec3((float)i, 0, -50), vec3((float)i, 0, 50), lineShader, &projection, &view);
		drawObject.push_back(linwidth2);
	}
}

void CAppEditer::addModel()
{
	Model*p = new Model("../../res/objects/backpack/backpack.obj",modelShader,lineShader,&projection,&view);
	drawObject.push_back(p);
	p->postion = glm::vec3(-5.0f, 2.5f, 0.1f);
	//p->S = vec3(0.5f, 1.0f, 0.5f);
	p->eulerAngle = vec3(45.0f, 0.0f,0.0f);
	//p->showBox();
	p->update();
	
	//Model*p2 = new Model(*p);
	//drawModel.push_back(p2);
	/*p2->postion = glm::vec3(-5.0f, 0.0f, 0.0f);
	p2->S = vec3(0.5f, 1.0f, 0.5f);
	p2->eulerAngle = vec3(0.0f, 0.0f,45.0f );
	p2->update();*/
}

void CAppEditer::addseleAxis()
{
	Eigen::Vector3f min_(0, 0, 0);
	Eigen::Vector3f max_(5, 5, 5);
	CArrowsAxis *p1 = new CArrowsAxis(min_, Eigen::Vector3f(min_(0), min_(1), max_(2)), lineShader, &projection, &view);
	p1->color = glm::vec4(0, 0, 1, 1);
	CArrowsAxis *p2 = new CArrowsAxis(min_, Eigen::Vector3f(min_(0), max_(1), min_(2)), lineShader, &projection, &view);
	p2->color = glm::vec4(0, 1, 0, 1);
	CArrowsAxis *p3 = new CArrowsAxis(min_, Eigen::Vector3f(max_(0), min_(1), min_(2)), lineShader, &projection, &view);
	p3->color = glm::vec4(1, 0, 0, 1);
	p1->mseleArrowsType = ESeleArrowsType::eZArrow;
	p2->mseleArrowsType = ESeleArrowsType::eYArrow;
	p3->mseleArrowsType = ESeleArrowsType::eXArrow;

	mselelaxis.push_back(p1);
	mselelaxis.push_back(p2);
	mselelaxis.push_back(p3);
	drawObject.push_back(p1);
	drawObject.push_back(p2);
	drawObject.push_back(p3);
}

void CAppEditer::addCube()
{
	auto cube = new CCube(&projection, &view, meshShader);
	cube->postion = glm::vec3(5.0f, 2.5f, 0.1f);
	cube->update();
	drawObject.push_back(cube);
}

void CAppEditer::addAxis()
{
	Eigen::Vector3f min_(0, 0, 0);
	Eigen::Vector3f max_(50, 50,50 );
	CArrowsAxis *p1 = new CArrowsAxis(min_, Eigen::Vector3f(min_(0), min_(1), max_(2)), lineShader, &projection, &view);
	p1->color = glm::vec4(0, 0, 1, 1);
	CArrowsAxis *p2 = new CArrowsAxis(min_, Eigen::Vector3f(min_(0), max_(1), min_(2)), lineShader, &projection, &view);
	p2->color = glm::vec4(0, 1, 0, 1);
	CArrowsAxis *p3 = new CArrowsAxis(min_, Eigen::Vector3f(max_(0), min_(1), min_(2)), lineShader, &projection, &view);
	p3->color = glm::vec4(1, 0, 0, 1);

	p1->DrawAlwaydepthTest = false;
	p2->DrawAlwaydepthTest = false;
	p3->DrawAlwaydepthTest = false;
	p1->actorType = EActorType::eGlobalAixs;
	p2->actorType = EActorType::eGlobalAixs;
	p3->actorType = EActorType::eGlobalAixs;

	drawObject.push_back(p1);
	drawObject.push_back(p2);
	drawObject.push_back(p3);
}

void CAppEditer::addPoint()
{
	//samperPoint.push_back({ 2,3.4 });
	//samperPoint.push_back({ 3,4.6 });
	//samperPoint.push_back({ 4,5.4 });
	//samperPoint.push_back({ 5,6.6 });
	//pointCould = new CPointCloud(samperPoint);
}

void CAppEditer::Load()
{
}

void CAppEditer::Unload()
{
}
void CAppEditer::eventAxis()
{
	for (auto item : mselelaxis)
	{
		if (item->isSelected)
		{
			CArrowsAxis *arrowp = (CArrowsAxis *)item;
			vec3 nowWPos = calcPlaneIntersectPoint(vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y),
				arrowp->model->postion - camera->Position,
				camera->Position, vec3(0));
			vec3 lastWPos = calcPlaneIntersectPoint(vec2(lastPos.x, lastPos.y), arrowp->model->postion - camera->Position,
				camera->Position, vec3(0));
			if (arrowp->mseleArrowsType == ESeleArrowsType::eXArrow)
			{
				arrowp->model->postion = arrowp->model->postion + vec3(nowWPos.x - lastWPos.x, 0, 0);
			}
			else if (arrowp->mseleArrowsType == ESeleArrowsType::eYArrow)
			{
				arrowp->model->postion = arrowp->model->postion + vec3(0, nowWPos.y - lastWPos.y, 0);
			}
			else if (arrowp->mseleArrowsType == ESeleArrowsType::eZArrow)
			{
				arrowp->model->postion = arrowp->model->postion + vec3(0, 0, nowWPos.z - lastWPos.z);
			}
			arrowp->model->update();
			mselelaxis[0]->postion = arrowp->model->postion; mselelaxis[1]->postion = arrowp->model->postion; mselelaxis[2]->postion = arrowp->model->postion;
			mselelaxis[0]->update(); mselelaxis[1]->update(); mselelaxis[2]->update();
		}
	}
}
void CAppEditer::Update()
{
	
	ImGuiIO& io = ImGui::GetIO();
	static bool moveAxiseActive = false;
	static bool showSeleAxiesActived = false;
	static CObject* showSAeleAxiesPara = nullptr;

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

	
	if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
	{
		float xoffset = ImGui::GetMousePos().x - lastPos.x;
		float yoffset = lastPos.y - ImGui::GetMousePos().y;

		camera->ProcessMouseMovement(xoffset, yoffset);
	}
	
	if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		float xoffset = ImGui::GetMousePos().x - lastPos.x;
		float yoffset = lastPos.y - ImGui::GetMousePos().y;
		bool moveFlag = (xoffset != 0) || (yoffset != 0);
		if (moveAxiseActive && moveFlag)
		{
			eventAxis();
		}
	}
	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		moveAxiseActive = false;

		if(showSeleAxiesActived)
		{
			showSeleAxiesActived = false;
			showseleAixs(showSAeleAxiesPara);
		}
	}
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		glm::vec3 posWorld =  getScreenWordPos({ ImGui::GetMousePos().x, ImGui::GetMousePos().y });
		
		CLinewidth1 *line = new CLinewidth1(vec3(camera->Position.x, camera->Position.y, camera->Position.z), posWorld, lineShader,
			&projection, &view);
		drawObject.push_back(line);
		
		bool noneIsSelet = true;
		for (auto item : drawObject)
		{
			if (item->actorType == EActorType::eModel||
				item->actorType == EActorType::eCube
				|| item->actorType== EActorType::eSeleAixs)
			{
				if (item->isHide == false)
				{
					bool flag = Geomery::TestRayAABBInterSection(camera->Position, glm::normalize(posWorld - camera->Position),
						vec3(item->boundingboxMin.x(), item->boundingboxMin.y(), item->boundingboxMin.z()),
						vec3(item->boundingboxMax.x(), item->boundingboxMax.y(), item->boundingboxMax.z()), item->modelMatrix);
					item->isSelected = flag;
					if (flag)
					{
						if (noneIsSelet)noneIsSelet = !noneIsSelet;
						if (item->actorType == EActorType::eModel||
							item->actorType == EActorType::eCube)
						{
							showSeleAxiesActived = true;
							showSAeleAxiesPara = item;
							
						}
						if (item->actorType == EActorType::eSeleAixs)
						{
							moveAxiseActive = true;
						}
					}
				}
			}
		}
		if (noneIsSelet) hideSeleAixs();
		//boost::thread my_thread_1([]() {while (1) { std::cout << "hello\n"; }});
	}
	
	lastPos = ImGui::GetMousePos();

	DrawWidget();
	
}

void CAppEditer::DrawWidget()
{
	view3dwidget->update();
}

void CAppEditer::showseleAixs(CObject * model)
{
	for (auto item : mselelaxis)
	{
		CArrowsAxis *axisP = (CArrowsAxis *)item;
		axisP->model = model;
		axisP->postion = model->postion;
		axisP->isHide = false;
		axisP->update();
	}
}

void CAppEditer::hideSeleAixs()
{
	for (auto item : mselelaxis)
	{
		CArrowsAxis *axisP = (CArrowsAxis *)item;
		axisP->isHide = true;
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
	
	// view/projection transformations
	projection = glm::perspective(glm::radians(camera->Zoom), (float)windowsW / (float)windowsH, 0.1f, 1000.0f);
	view = camera->GetViewMatrix();

	for (auto &itemModel : drawObject)
	{
		itemModel->Draw();
	}

	//meshShader->use();
	//meshShader->setMat4("projection", projection);
	//meshShader->setMat4("view", view);
	//for (auto &itemMesh : drawMesh)
	//{
	//	meshShader->setMat4("model", itemMesh->modelMatrix);
	//	itemMesh->Draw();
	//}

	//for (auto &itemline : drawLine)
	//{
	//	meshShader->setMat4("model", itemline->modelMatrix);
	//	itemline->Draw();
	//}

	//meshShader->setMat4("model", pointCould->modelMatrix);
	//pointCould->Draw();

	/*glDepthFunc(GL_ALWAYS);
	lineShader->use();
	lineShader->setMat4("projection", projection);
	lineShader->setMat4("view", view);
	for (auto &itemline : drawLineWidth1s)
	{
		lineShader->setMat4("model", itemline->modelMatrix);
		lineShader->setVec4("ourColor", vec4(1,1,1,1));
		itemline->Draw();
	}
	glDepthFunc(GL_LESS);*/
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

vec3 CAppEditer::calcPlaneIntersectPoint(glm::vec2 mousePos, vec3 normal, vec3 sPoint, vec3 point1Plane)
{
	vec3 ret;
	vec3 endpoint =  getScreenWordPos(mousePos);
	vec3 dirV = endpoint - sPoint;
	float dDN = glm::dot(dirV, normal);
	if (dDN < 0.00000001f && dDN > -0.00000001f)
	{
		return vec3(0.0f);
	}

	float t;
	t = glm::dot((point1Plane - sPoint), normal) / dDN;
	ret = sPoint + t * dirV;

	return ret;
}



