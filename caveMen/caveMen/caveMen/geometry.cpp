#include "geometry.h"
namespace Geomery
{
	/*
	P=O+tD
	(v1−P)⋅n=0
	t= ((v1-o)⋅n)/(D⋅n)
	*/
	bool intersectRayPolygon(vec3 oV, vec3 dirV, vec3 point1, vec3 point2, vec3 point3)
	{
		vec3 v1 = point2 - point1;
		vec3 v2 = point3 - point1;
		vec3 n = glm::normalize(glm::cross(v2, v1)) ;
		float t;
		t = glm::dot((point1 - oV),n) / glm::dot(dirV, n);
		
		vec3 p = oV + t * dirV;
	}
};