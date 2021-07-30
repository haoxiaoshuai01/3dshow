#pragma once
#include <iostream>
#include <vector>
class Camera; 
class Shader;
class Model;
class CMesh;
class CLine;
class CAppEditer
{
public:
	CAppEditer();
	~CAppEditer();
	void addMesh();
	void addLine();
	void addModel();
	void init();
	void Load();
	void Unload();
	void Update();
	void Draw();
	int windowsW;
	int windowsH;
private:
	Camera *camera;
	Shader *modelShader;
	Shader *meshShader;
	std::vector<Model *> drawModel;
	std::vector<CMesh *> drawMesh;
	std::vector<CLine *> drawLine;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

