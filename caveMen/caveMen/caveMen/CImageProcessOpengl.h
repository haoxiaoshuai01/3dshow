#pragma once
#include "dataStruct.h"
#include <learnopengl/shader_m.h>
class CImageProcessOpengl
{
	public:
		CImageProcessOpengl(unsigned char *_imageData, unsigned int _width, unsigned int _height, unsigned int _comp);
		~CImageProcessOpengl();
		
		void runProcess();
	private:
		void setupProcessFbo();
		void setupFaceVBO();
		void drawFaceToGpu();
		void genTextureId();
		unsigned char *imageData;
		unsigned int width;
		unsigned int height;
		unsigned int comp;
		unsigned int textureID = 0;
		unsigned int framebuffer;
		unsigned int fboTexture;
		// screen quad VAO
		unsigned int quadVAO, quadVBO;
		Shader *fuzzyShader;
};

