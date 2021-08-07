#include "geometry.h"
namespace Geomery
{
	/*
	P=O+tD
	(v1−P)⋅n=0
	t= ((v1-o)⋅n)/(D⋅n)
	*/
	bool SameSide(vec3 A, vec3 B, vec3 C, vec3 P)
	{
		vec3 AB = B - A;
		vec3 AC = C - A;
		vec3 AP = P - A;

		vec3 v1 = glm::cross(AB, AC);
		vec3 v2 = glm::cross(AB, AP);
		float lv2 = glm::length(v2);
		if (lv2 < 0.000001f && lv2 >-0.000001f)
		{
			return true;
		}
		float d = glm::dot(glm::normalize(v1), glm::normalize(v2));
		// v1 and v2 should point to the same direction
		//return v1.Dot(v2) >= 0 ;
		return  d > 0;
	};
	bool intersectRayPolygon(vec3 oV, vec3 dirV, vec3 point1, vec3 point2, vec3 point3)
	{
		vec3 v1 = point2 - point1;
		vec3 v2 = point3 - point1;
		vec3 n = glm::normalize(glm::cross(v2, v1)) ;

	   float dDN =  glm::dot(dirV, n);
	   if (dDN < 0.00000001f && dDN > -0.00000001f)
	   {
		   return false;
	   }

		float t;
		t = glm::dot((point1 - oV),n) / dDN;
		vec3 p = oV + t * dirV;

		auto isInTrangle = 
			[](vec3 point1,vec3 point2,vec3 point3,vec3 p ) 
		{
			return SameSide(point1, point2, point3, p) && SameSide(point2, point3, point1, p) &&
				SameSide(point3, point1, point2, p);
		};
		
		return isInTrangle(point1, point2, point3, p);

	}
};