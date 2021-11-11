#include "CPointCloud.h"

CPointCloud::CPointCloud()
{
	//this->postions = postions;
	updateVectorCloud();
	setupMesh();
}

void CPointCloud::updateVectorCloud()
{
	/*int triangleAmount = 15;
	float radius = 0.05f;
	float rad360 = 2 * glm::pi<float>();
	for (int iPos=0; iPos <postions.size(); iPos++)
	{
		vertices.push_back(SVertex(glm::vec3(postions[iPos].x ,postions[iPos].y,z), glm::vec3(0.2, 0.4, 0.2)));
		for (int i = 0; i < triangleAmount; i++)
		{
			SVertex v( glm::vec3( postions[iPos].x + (radius * cos(i *  rad360 / triangleAmount)),
				postions[iPos].y + (radius * sin(i * rad360 / triangleAmount)),
				z),
				glm::vec3(0.2, 0.4, 0.2)
				);
			vertices.push_back(v);
			if (i > 0)
			{
				indices.push_back(iPos *  (triangleAmount+1));
				indices.push_back(iPos *  (triangleAmount +1) +1+ i - 1);
				indices.push_back(iPos * (triangleAmount + 1) +1+i);

			}
			if (i == (triangleAmount - 1))
			{
				indices.push_back(iPos *  (triangleAmount + 1));
				indices.push_back(iPos * (triangleAmount + 1) + 1 + i);
				indices.push_back(iPos * (triangleAmount + 1) + 1 );
			}
		}

	}*/
}

void CPointCloud::Draw()
{

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void CPointCloud::setupMesh()
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SVertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Color));

	glBindVertexArray(0);
}
