#include "CLIne.h"

CLine::CLine(glm::vec2 startv, glm::vec2 endv)
{
	start = startv;
	endP = endv;
	vertices.resize(4);
	indices.resize(6);
	updateVertex();
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Color));

	glBindVertexArray(0);


}

void CLine::updateVertex()
{
	vertices.clear();
	indices.clear();


	//x����������н�
	float consRad = glm::dot(glm::normalize(endP - start), glm::normalize(glm::vec2(1, 0)));
	float angleRad = glm::acos(consRad);
	if (consRad < 0)
	{
		angleRad = glm::pi<float>() - angleRad;
	}

	
	vertices.push_back(SVertex(glm::vec3(start.x-Lwidth/2* glm::cos(consRad), 
		start.y + Lwidth / 2 * glm::sin(consRad), z), glm::vec3(0.6, 0.6, 0.2)));
	vertices.push_back(SVertex(glm::vec3(endP.x - Lwidth / 2 * glm::cos(consRad),
		endP.y + Lwidth / 2 * glm::sin(consRad), z), glm::vec3(0.6, 0.6, 0.2)));
	vertices.push_back(SVertex(glm::vec3(start.x + Lwidth / 2 * glm::cos(consRad),
		start.y - Lwidth / 2 * glm::sin(consRad), z), glm::vec3(0.6, 0.6, 0.2)));
	vertices.push_back(SVertex(glm::vec3(endP.x + Lwidth / 2 * glm::cos(consRad),
		endP.y - Lwidth / 2 * glm::sin(consRad), z), glm::vec3(0.6, 0.6, 0.2)));
	
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
}

void CLine::Draw()
{
	// draw mesh
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SVertex), &vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
