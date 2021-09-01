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
	static CAppEditer * Instance();
	static CAppEditer *myp;
	~CAppEditer();
	void SetupFbo();
	void addMesh();
	void addSkyBox();
	void addGridLine();
	void addModel();
	void addseleAxis();
	void addBilboard();
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
	glm::mat4 projection;
	glm::mat4 view;
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
	Shader *meshBillboardShader;
	std::vector<CObject *> drawObject;
	std::vector<CObject *> mselelaxis;
	CMesh * testMesh;
	//std::vector<CLine *> drawLine;
	//std::vector<CLinewidth1 *> drawLineWidth1s;
	
	//CPointCloud *pointCould;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	ImVec2 lastPos;

	unsigned int framebuffer = 0;
	unsigned int textureColorbuffer = 0;

	unsigned int testTexture = 0;
	
};

