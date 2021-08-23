#include "CCube.h"

CCube::CCube( glm::mat4 * pro, glm::mat4 * view,Shader *shader):
	mshader(shader),mview(view),mpro(pro)
{
	actorType = EActorType::eCube;
	vertices.push_back(SVertex(vec3(-1.0f, -1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, -1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, 1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, 1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));

	vertices.push_back(SVertex(vec3(-1.0f, -1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, -1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, 1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, 1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));

	vertices.push_back(SVertex(vec3(-1.0f, 1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, 1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, -1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, -1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));

	vertices.push_back(SVertex(vec3(1.0f, 1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, 1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, -1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, -1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));

	vertices.push_back(SVertex(vec3(-1.0f, -1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, -1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, -1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, -1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));

	vertices.push_back(SVertex(vec3(-1.0f, 1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, 1.0f, -1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(1.0f, 1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));
	vertices.push_back(SVertex(vec3(-1.0f, 1.0f, 1.0f), vec3(0.7, 0.7, 0.7)));

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(0 + 4);
	indices.push_back(1 + 4);
	indices.push_back(2 + 4);
	indices.push_back(2 + 4);
	indices.push_back(3 + 4);
	indices.push_back(0 + 4);

	indices.push_back(0 + 8);
	indices.push_back(1 + 8);
	indices.push_back(2 + 8);
	indices.push_back(2 + 8);
	indices.push_back(3 + 8);
	indices.push_back(0 + 8);

	indices.push_back(0 + 12);
	indices.push_back(3 + 12);
	indices.push_back(2 + 12);
	indices.push_back(2 + 12);
	indices.push_back(1 + 12);
	indices.push_back(0 + 12);

	indices.push_back(0 + 16);
	indices.push_back(1 + 16);
	indices.push_back(2 + 16);
	indices.push_back(2 + 16);
	indices.push_back(3 + 16);
	indices.push_back(0 + 16);

	indices.push_back(0 + 20);
	indices.push_back(3 + 20);
	indices.push_back(2 + 20);
	indices.push_back(2 + 20);
	indices.push_back(1 + 20);
	indices.push_back(0 + 20);
	setupMesh();
	Eigen::Matrix<float, Eigen::Dynamic, 3> m;
	m.resize(vertices.size(),3);
	int i = 0;
	for (auto item : vertices)
	{
		m(i, 0) = item.Position.x;
		m(i, 1) = item.Position.y;
		m(i, 2) = item.Position.z;
		i++;

	}
	std::cout << m << "\n";
	genboundingbox(m);
}

void CCube::Draw()
{
	mshader->use();
	mshader->setMat4("projection", *mpro);
	mshader->setMat4("view", *mview);
	mshader->setMat4("model", modelMatrix);

	// draw mesh
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CCube::setupMesh()
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
	// vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Color));

	glBindVertexArray(0);
}
