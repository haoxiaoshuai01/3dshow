#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <GL/gl3w.h>
using namespace glm;
struct SVertex
{
	SVertex()
	{
	}
	SVertex(glm::vec3 Position, glm::vec3 Color):Position(Position), Color(Color)
	{}
	// position
	glm::vec3 Position;
	// Color
	glm::vec3 Color;
};
struct Point
{
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	float x;
	float y;
};