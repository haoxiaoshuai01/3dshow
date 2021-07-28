#pragma once
#include <iostream>
#include <vector>
class Camera; 
class Shader;
class Model;
class CAppEditer
{
public:
	CAppEditer();
	~CAppEditer();
	void init();
	void Load();
	void Unload();
	void Update();
	void Draw(int w,int h);
private:
	Camera *camera;
	Shader *ourShader;
	std::vector<Model *> drawModel;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};

