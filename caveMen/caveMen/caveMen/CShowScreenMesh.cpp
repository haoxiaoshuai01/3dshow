#include "CShowScreenMesh.h"
//float quadVertices[] = {   // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//	 positions   // texCoords
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	-1.0f, -1.0f,  0.0f, 0.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//	 1.0f,  1.0f,  1.0f, 1.0f
//};
//unsigned int quadVAO, quadVBO;
CShowScreenMesh::CShowScreenMesh(unsigned int *screenTexture_)
{
	screenTexture = screenTexture_;
	vertices.push_back(DataV({ -1.0f,  1.0f }, { 0.0f, 1.0f }));
	vertices.push_back(DataV({ -1.0f, -1.0f }, { 0.0f, 0.0f }));
	vertices.push_back(DataV({ 1.0f, -1.0f }, { 1.0f, 0.0f }));
	vertices.push_back(DataV({ 1.0f,  1.0f }, { 1.0f, 1.0f }));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);


	 // setup screen VAO

	//glGenVertexArrays(1, &quadVAO);
	//glGenBuffers(1, &quadVBO);
	//glBindVertexArray(quadVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	setupMesh();
}

void CShowScreenMesh::Draw()
{
	CAppEditer::Instance()->aftertreatmentShader->use();
	CAppEditer::Instance()->aftertreatmentShader->setInt("screenTexture", 0);
	// draw mesh
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *screenTexture); // use the now resolved color attachment as the quad's texture
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glBindVertexArray(quadVAO);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, *screenTexture); // use the now resolved color attachment as the quad's texture
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CShowScreenMesh::setupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DataV), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DataV), (void*)0);
	// vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(DataV), (void*)offsetof(DataV, TexCoords));

	glBindVertexArray(0);
}
