#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
namespace Geomery
{
	bool SameSide(vec3 A, vec3 B, vec3 C, vec3 P);
	bool intersectRayPolygon(vec3 oV,vec3 dirV,vec3 point1 ,vec3 point2,vec3 point3);
};
