#include "geometry.h"
#include <algorithm>
#include "Eigen/Core"
#include <Eigen/Geometry>
#define EPSINON  0.0001f
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

	bool TestRayOBBIntersection(
		glm::vec3 ray_origin,        // Ray origin, in world space
		glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
		glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
		glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
		glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
		float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
	) {

		// Intersection method from Real-Time Rendering and Essential Mathematics for Games

		float tMin = 0.0f;
		float tMax = 100000.0f;

		glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

		glm::vec3 delta = OBBposition_worldspace - ray_origin;

		// Test intersection with the 2 planes perpendicular to the OBB's X axis
		{
			glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
			float e = glm::dot(xaxis, delta);
			float f = glm::dot(ray_direction, xaxis);

			if (fabs(f) > 0.001f) { // Standard case

				float t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
				float t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
				// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

				// We want t1 to represent the nearest intersection, 
				// so if it's not the case, invert t1 and t2
				if (t1 > t2) {
					float w = t1; t1 = t2; t2 = w; // swap t1 and t2
				}

				// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
				if (t2 < tMax)
					tMax = t2;
				// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
				if (t1 > tMin)
					tMin = t1;

				// And here's the trick :
				// If "far" is closer than "near", then there is NO intersection.
				// See the images in the tutorials for the visual explanation.
				if (tMax < tMin)
					return false;

			}
			else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
				if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f)
					return false;
			}
		}


		// Test intersection with the 2 planes perpendicular to the OBB's Y axis
		// Exactly the same thing than above.
		{
			glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
			float e = glm::dot(yaxis, delta);
			float f = glm::dot(ray_direction, yaxis);

			if (fabs(f) > 0.001f) {

				float t1 = (e + aabb_min.y) / f;
				float t2 = (e + aabb_max.y) / f;

				if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

				if (t2 < tMax)
					tMax = t2;
				if (t1 > tMin)
					tMin = t1;
				if (tMin > tMax)
					return false;

			}
			else {
				if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
					return false;
			}
		}


		// Test intersection with the 2 planes perpendicular to the OBB's Z axis
		// Exactly the same thing than above.
		{
			glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
			float e = glm::dot(zaxis, delta);
			float f = glm::dot(ray_direction, zaxis);

			if (fabs(f) > 0.001f) {

				float t1 = (e + aabb_min.z) / f;
				float t2 = (e + aabb_max.z) / f;

				if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

				if (t2 < tMax)
					tMax = t2;
				if (t1 > tMin)
					tMin = t1;
				if (tMin > tMax)
					return false;

			}
			else {
				if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
					return false;
			}
		}

		intersection_distance = tMin;
		return true;

	}

	bool TestRayAABBInterSection(glm::vec3 ray_origin, glm::vec3 ray_direction, glm::vec3 aabb_min, glm::vec3 aabb_max, glm::mat4 ModelMatrix)
	{
		int ret = false;
		vec4 aabbMin = ModelMatrix * glm::vec4(aabb_min,1.0f);
		vec4 aabbMax = ModelMatrix * glm::vec4(aabb_max,1.0f);
		
		aabbMin = aabbMin / aabbMin[3];
		aabbMax = aabbMax / aabbMax[3];
		
		//y-z plane
		{
			{
				float txnear = -FLT_MAX;
				float txFar = FLT_MAX;
				float tynear = -FLT_MAX;
				float tyFar = FLT_MAX;
				float tznear = -FLT_MAX;
				float tzFar = FLT_MAX;
				if (std::abs(ray_direction.x) > EPSINON)
				{
					txnear = (aabbMin.x - ray_origin.x) / ray_direction.x;
					txFar = (aabbMax.x - ray_origin.x) / ray_direction.x;

					if (txnear > txFar)
					{
						float tmp = txnear;
						txnear = txFar;
						txFar = tmp;
					}

				}
				if (std::abs(ray_direction.y) > EPSINON)
				{
					tynear = (aabbMin.y - ray_origin.y) / ray_direction.y;
					tyFar = (aabbMax.y - ray_origin.y) / ray_direction.y;

					if (tynear > tyFar)
					{
						float tmp = tynear;
						tynear = tyFar;
						tyFar = tmp;
					}
				}

				if (std::abs(ray_direction.z) > EPSINON)
				{
					tznear = (aabbMin.z - ray_origin.z) / ray_direction.z;
					tzFar = (aabbMax.z - ray_origin.z) / ray_direction.z;

					if (tznear > tzFar)
					{
						float tmp = tznear;
						tznear = tzFar;
						tzFar = tmp;
					}
				}

				
				float t0 = Eigen::Vector3f(txnear, tynear, tznear).maxCoeff();
				float t1 = Eigen::Vector3f(txFar,tyFar,tzFar).minCoeff();
				if (t0 < t1)
				{
					ret = true;
				}
			}
		}

		return ret;
	}


};