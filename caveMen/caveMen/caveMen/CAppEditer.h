#pragma once

#include <iostream>
#include <vector>
#include "CObject.h"
#include "imgui.h"
time_t getTimeStamp();
class Camera; 
class Shader;
class Model;
class CMesh;
class CLine;
class CPointCloud;
class CLinewidth1;
class C3DViewPortWidget;
class CAppEditer
{
public:
	CAppEditer();
	~CAppEditer();
	void addMesh();
	void addSkyBox();
	void addGridLine();
	void addModel();
	void addseleAxis();
	void addCube();
	void addAxis();
	void addPoint();
	void init();
	void Load();
	void Unload();
	void Update();
	void DrawWidget();
	void showseleAixs(CObject *model);
	void hideSeleAixs();
	void Draw();
	glm::vec3 getScreenWordPos(glm::vec2 pos);
	int windowsW;
	int windowsH;
private:
	glm::vec3 calcPlaneIntersectPoint(glm::vec2 mousePos, glm::vec3 normal, glm::vec3 sPoint, glm::vec3 point1Plane);
	void eventAxis();
private:
	C3DViewPortWidget *view3dwidget;
	Camera *camera;
	Shader *modelShader;
	Shader *meshShader;
	Shader *lineShader;
	Shader *skyboxShader;
	std::vector<CObject *> drawObject;
	std::vector<CObject *> mselelaxis;
	//std::vector<CMesh *> drawMesh;
	//std::vector<CLine *> drawLine;
	//std::vector<CLinewidth1 *> drawLineWidth1s;
	
	//CPointCloud *pointCould;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	ImVec2 lastPos;
	glm::mat4 projection;
	glm::mat4 view;
	
};

