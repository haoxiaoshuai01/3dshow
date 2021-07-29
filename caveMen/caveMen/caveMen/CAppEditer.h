#pragma once
#include <iostream>
#include <vector>
class Camera; 
class Shader;
class Model;
class CMesh;
class CAppEditer
{
public:
	CAppEditer();
	~CAppEditer();
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
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

