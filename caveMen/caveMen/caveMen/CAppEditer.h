#pragma once

#include <iostream>
#include <vector>
#include "CObject.h"
time_t getTimeStamp();
class Camera; 
class Shader;
class Model;
class CMesh;
class CLine;
class CPointCloud;
class CLinewidth1;
class CAppEditer
{
public:
	CAppEditer();
	~CAppEditer();
	void addMesh();
	void addLine();
	void addModel();
	void addPoint();
	void init();
	void Load();
	void Unload();
	void Update();
	void Draw();
	glm::vec3 getScreenWordPos(glm::vec2 pos);
	int windowsW;
	int windowsH;
private:
	Camera *camera;
	Shader *modelShader;
	Shader *meshShader;
	Shader *lineShader;
	std::vector<Model *> drawModel;
	std::vector<CMesh *> drawMesh;
	std::vector<CLine *> drawLine;
	std::vector<CLinewidth1 *> drawLineWidth1s;
	
	CPointCloud *pointCould;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	glm::mat4 projection;
	glm::mat4 view;
};

