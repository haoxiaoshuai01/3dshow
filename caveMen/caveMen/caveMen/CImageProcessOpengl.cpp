#include "CImageProcessOpengl.h"



CImageProcessOpengl::CImageProcessOpengl(unsigned char * _imageData, unsigned int _width, unsigned int _height, unsigned int _comp)
{
	imageData = _imageData;
	width = _width;
	height = _height;
	comp = _comp;

}

CImageProcessOpengl::~CImageProcessOpengl()
{
	glDeleteTextures(1, &textureID);
	glDeleteTextures(1, &fboTexture);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
	glDeleteFramebuffers(1, &framebuffer);
	delete fuzzyShader;

}

void CImageProcessOpengl::runProcess()
{
	fuzzyShader = new Shader(
		"#version 330 core                                      "
		"layout (location = 0) in vec2 aPos;                    "
		"layout (location = 1) in vec2 aTexCoords;              "
		"                                                       "
		"out vec2 TexCoords;                                    "
		"                                                       "
		"void main()                                            "
		"{                                                      "
		"    TexCoords = aTexCoords;                            "
		"    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);      "
		"}                                                      ",

		"#version 330 core                                                                             "
		"out vec4 FragColor;                                                                           "
		"                                                                                              "
		"in vec2 TexCoords;                                                                            "
		"                                                                                              "
		"uniform sampler2D screenTexture;                                                              "
		"vec3 convolution( float kernel[9])                                                            "
		"{                                                                                             "
		"	const float offset = 1.0 / 300.0;                                                          "
		"	vec2 offsets[9] = vec2[](                                                                  "
		"        vec2(-offset,  offset), // 左上                                                       "
		"        vec2( 0.0f,    offset), // 正上                                                       "
		"        vec2( offset,  offset), // 右上                                                       "
		"        vec2(-offset,  0.0f),   // 左                                                         "
		"        vec2( 0.0f,    0.0f),   // 中                                                         "
		"        vec2( offset,  0.0f),   // 右                                                         "
		"        vec2(-offset, -offset), // 左下                                                       "
		"        vec2( 0.0f,   -offset), // 正下                                                       "
		"        vec2( offset, -offset)  // 右下                                                       "
		"    );                                                                                        "
		"    vec3 sampleTex[9];                                                                        "
		"    for(int i = 0; i < 9; i++)                                                                "
		"    {                                                                                         "
		"        sampleTex[i] = vec3(texture(screenTexture, TexCoords.xy + offsets[i]));               "
		"    }                                                                                         "
		"    vec3 col = vec3(0.0);                                                                     "
		"    for(int i = 0; i < 9; i++)                                                                "
		"        col += sampleTex[i] * kernel[i];                                                      "
		"                                                                                              "
		"		return col;                                                                            "
		"}                                                                                             "
		"vec3 GaussianBlur()                                                                           "
		"{                                                                                             "
		"                                                                                              "
		"	float kernel[9] = float[](                                                                 "
		"		1.0 / 16, 2.0 / 16, 1.0 / 16,                                                          "
		"		2.0 / 16, 4.0 / 16, 2.0 / 16,                                                          "
		"		1.0 / 16, 2.0 / 16, 1.0 / 16                                                           "
		"	);                                                                                         "
		"                                                                                              "
		"	return convolution(kernel);                                                                "
		"}                                                                                             "
		"                                                                                              "
		"void main()                                                                                   "
		"{                                                                                             "
		"	                                                                                           "
		"	vec3 middleValue;                                                                          "
		"	middleValue = GaussianBlur();                                                              "
		"	FragColor =vec4(middleValue,1.0);                                                          "
		"}                                                                                             ",
		true
	);
	setupFaceVBO();
	genTextureId();
	setupProcessFbo();
	drawFaceToGpu();
}

void CImageProcessOpengl::setupProcessFbo()
{
	// framebuffer configuration
	// -------------------------
	
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	
	glGenTextures(1, &fboTexture);
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
		
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CImageProcessOpengl::setupFaceVBO()
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void CImageProcessOpengl::drawFaceToGpu()
{
	// bind to framebuffer and draw scene as we normally would to color texture 
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// make sure we clear the framebuffer's content
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	fuzzyShader->use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureID);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CImageProcessOpengl::genTextureId()
{
	glGenTextures(1, &textureID);
	if (imageData)
	{
		GLenum format;
		if (comp == 1)
			format = GL_RED;
		else if (comp == 3)
			format = GL_RGB;
		else if (comp == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "no image data" << std::endl;
	}
}
