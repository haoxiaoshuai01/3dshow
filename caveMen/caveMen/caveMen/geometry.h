#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
namespace Geomery
{
	bool intersectRayPolygon(vec3 oV,vec3 dirV,vec3 point1 ,vec3 point2,vec3 point3);
};

