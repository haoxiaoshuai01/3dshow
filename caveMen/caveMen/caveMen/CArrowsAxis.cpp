#include "CArrowsAxis.h"

CArrowsAxis::CArrowsAxis(Eigen::Vector3f sourcePoint, Eigen::Vector3f endPoint, 
	Shader* lineshader, glm::mat4 *project, glm::mat4 *lookat):CObject()
{
	mlineshader = lineshader;
	mproject = project;
	mlookat = lookat;


	addVertices(sourcePoint, endPoint);
	setup();
	Eigen::Matrix<float, Eigen::Dynamic, 3> m;
	int i = 0;
	m.resize(vertices.size(), 3);
	for (auto v : vertices)
	{
		m(i, 0) = v.Position.x;
		m(i, 1) = v.Position.y;
		m(i, 2) = v.Position.z;
		i++;
	}
	genboundingbox(m);
}

void CArrowsAxis::addVertices(Eigen::Vector3f sourcePoint, Eigen::Vector3f endPoint)
{
	Eigen::Vector3f direction = endPoint-sourcePoint;
	
	int triangleAmount = 15;
	float radius = 0.1f;
	float rad360 = 2 * glm::pi<float>();
	glm::vec3 color(0.2, 0.4, 0.2);
	Eigen::Vector3f oldNormoal(0.0f, 0.0f, 1.0f);
	float destinsAcrros = direction.norm()/5.0f;

	Eigen::Vector3f rotationAxis(oldNormoal.cross(direction));
	float iPos = 0;
	
	vertices.push_back(SVertex(glm::vec3(endPoint.x(), endPoint.y(), endPoint.z()), color));
	for (int i = 0; i < triangleAmount; i++)
	{
		SVertex v(glm::vec3(endPoint.x() + (radius * cos(i *  rad360 / triangleAmount)),
			endPoint.y() + (radius * sin(i * rad360 / triangleAmount)),
			endPoint.z()-destinsAcrros),
			color);
		vertices.push_back(v);
		indices.push_back(iPos *  (triangleAmount + 1));
		indices.push_back(iPos * (triangleAmount + 1) + 1 + i);
		indices.push_back(iPos *  (triangleAmount + 1) + 1 + (i + 1) % triangleAmount);
	}
	iPos = 1;
	vertices.push_back(SVertex(glm::vec3(sourcePoint.x(), sourcePoint.y(), sourcePoint.z()), color));
	for (int i = 0; i < triangleAmount; i++)
	{
		SVertex v(glm::vec3(sourcePoint.x() + (radius * cos(i *  rad360 / triangleAmount)),
			sourcePoint.y() + (radius * sin(i * rad360 / triangleAmount)),
			sourcePoint.z()),
			color);
		vertices.push_back(v);
		indices.push_back(iPos *  (triangleAmount + 1));
		indices.push_back(iPos * (triangleAmount + 1) + 1 + i);
		indices.push_back(iPos *  (triangleAmount + 1) + 1 + (i + 1)% triangleAmount);
		
		indices.push_back(iPos * (triangleAmount + 1) + 1 + i);
		indices.push_back(iPos *  (triangleAmount + 1) + 1 + (i + 1) % triangleAmount);
		indices.push_back((iPos-1) * (triangleAmount + 1) + 1 + i);

		indices.push_back((iPos - 1) * (triangleAmount + 1) + 1 + i);
		indices.push_back((iPos - 1) * (triangleAmount + 1) + 1 + (i+1)% triangleAmount);
		indices.push_back(iPos * (triangleAmount + 1) + 1 + (i + 1) % triangleAmount);
	}
	
}

void CArrowsAxis::setup()
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

void CArrowsAxis::Draw(glm::mat4 *modelMat)
{
	mlineshader->use();
	mlineshader->setMat4("projection", *mproject);
	mlineshader->setMat4("view", *mlookat);
	mlineshader->setMat4("model",* modelMat);

	mlineshader->setVec4("ourColor", vec4(0, 1, 0, 1));
	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
