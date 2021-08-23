#include "CSkybox.h"
#include <string>

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
CSkybox::CSkybox(Shader*skyboxShader, glm::mat4 *pro, glm::mat4 *view) :
	mSkyboxShader(skyboxShader),mPro(pro), mView(view)
{
	actorType = EActorType::eSkyBox;
	vertices = {
		// positions          
	vec3(-1.0f,  1.0f, -1.0f),
	vec3(-1.0f, -1.0f, -1.0f),
	vec3(1.0f, -1.0f, -1.0f),
	vec3(1.0f, -1.0f, -1.0f),
	vec3(1.0f,  1.0f, -1.0f),
	vec3(-1.0f,  1.0f, -1.0f),

	vec3(-1.0f, -1.0f,  1.0f),
	vec3(-1.0f, -1.0f, -1.0f),
	vec3(-1.0f,  1.0f, -1.0f),
	vec3(-1.0f,  1.0f, -1.0f),
	vec3(-1.0f,  1.0f,  1.0f),
	vec3(-1.0f, -1.0f,  1.0f),

	vec3(1.0f, -1.0f, -1.0f),
	vec3(1.0f, -1.0f,  1.0f),
	vec3(1.0f,  1.0f,  1.0f),
	vec3(1.0f,  1.0f,  1.0f),
	vec3(1.0f,  1.0f, -1.0f),
	vec3(1.0f, -1.0f, -1.0f),

	vec3(-1.0f, -1.0f,  1.0f),
	vec3(-1.0f,  1.0f,  1.0f),
	vec3( 1.0f,  1.0f,  1.0f),
	vec3( 1.0f,  1.0f,  1.0f),
	vec3( 1.0f, -1.0f,  1.0f),
	vec3(-1.0f, -1.0f,  1.0f),

	vec3(-1.0f,  1.0f, -1.0f),
	vec3( 1.0f,  1.0f, -1.0f),
	vec3( 1.0f,  1.0f,  1.0f),
	vec3( 1.0f,  1.0f,  1.0f),
	vec3(-1.0f,  1.0f,  1.0f),
	vec3(-1.0f,  1.0f, -1.0f),

	vec3(-1.0f, -1.0f, -1.0f),
	vec3(-1.0f, -1.0f,  1.0f),
	vec3(1.0f, -1.0f, -1.0f),
	vec3(1.0f, -1.0f, -1.0f),
	vec3(-1.0f, -1.0f,  1.0f),
	vec3(1.0f, -1.0f,  1.0f)
	};
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

	glBindVertexArray(0);

	std::vector<std::string> faces
	{
		("../../res/textures/skybox/right.jpg"),
		("../../res/textures/skybox/left.jpg"),
		("../../res/textures/skybox/top.jpg"),
		("../../res/textures/skybox/bottom.jpg"),
		("../../res/textures/skybox/front.jpg"),
		("../../res/textures/skybox/back.jpg")
	};
	cubemapTexture = loadCubemap(faces);

}

CSkybox::~CSkybox()
{
}

void CSkybox::Draw()
{
	mSkyboxShader->use();
	mSkyboxShader->setInt("skybox", 0);
	mSkyboxShader->setMat4("projection", *mPro);
	mSkyboxShader->setMat4("view", glm::mat4(glm::mat3(*mView)));
	
	
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}
