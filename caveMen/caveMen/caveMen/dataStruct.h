#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <GL/gl3w.h>
struct SVertex
{
	SVertex(glm::vec3 Position, glm::vec3 Color):Position(Position), Color(Color)
	{}
	// position
	glm::vec3 Position;
	// Color
	glm::vec3 Color;
};