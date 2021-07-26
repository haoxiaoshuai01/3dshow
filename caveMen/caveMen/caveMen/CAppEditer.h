#pragma once

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
	void Draw();
private:
	//Camera *camera;
	//Shader *ourShader;
	//Model *ourModel;
};

