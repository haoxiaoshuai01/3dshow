
#include <algorithm>
#include <iostream>

#include <vector>
#include <map>	
#include <string>
#include <functional>

using type_pt3d = std::tuple<float, float, float>;
using type_pt2d = std::tuple<float, float>;
using type_func_constraint = std::function<void(void)>;
using type_polygon = std::vector<type_pt2d>;


enum class  EPolygonStatus
{
	Einside = 0,
	Eexternal,
	EparallelInside,
	EparallelExternal,
	Eintersect,
};
struct Box
{
	type_polygon toPolygon2d()
	{
		type_polygon polygon;
		auto[x, y] = pt_lt2d;
		polygon.emplace_back(pt_lt2d);
		polygon.emplace_back(std::make_tuple(x + length, y));
		polygon.emplace_back(std::make_tuple(x + length, y + width));
		polygon.emplace_back(std::make_tuple(x, y + width));
		return polygon;
	}
	type_pt3d center{ 0,0,0 };
	type_pt2d pt_lt2d;	//2维里面的左上角坐标
	float width{ 0 };
	float height{ 0 };
	float length{ 0 };
};

struct Lineseg
{
	Lineseg(type_pt2d s, type_pt2d e) :s(s), e(e)
	{}
	type_pt2d s;
	type_pt2d e;
};

// 计算叉积
float multiply(type_pt2d sp, type_pt2d ep, type_pt2d op)
{
	auto[x_sp, y_sp] = sp;
	auto[x_ep, y_ep] = ep;
	auto[x_op, y_op] = op;


	return (x_sp - x_op) * (y_ep - y_op) - (x_ep - x_op) * (y_sp - y_op);
}

bool isparallel(Lineseg u, Lineseg v)
{
	return false;
}
bool isLineOverlap(type_pt2d u, type_pt2d v)
{
	return false;
}
enum class EIntersectStatus
{
	EIntersectHasVectex,
	EIntersectNonVectex,
	EnonIntersect
};
// 判断线段是否相交 
EIntersectStatus intersect(Lineseg u, Lineseg v)
{
	//auto[x_us, y_us] = u.s;
	//auto[x_ue, y_ue] = u.e;
	//auto[x_vs, y_vs] = v.s;
	//auto[x_ve, y_ve] = v.e;
	//return((std::max(x_us, x_ue) >= std::min(x_vs, x_ve)) &&                     //排斥实验 
	//	(std::max(x_vs, x_ve) >= std::min(x_us, x_ue)) &&
	//	(std::max(y_us, y_ue) >= std::min(y_vs, y_ve)) &&
	//	(std::max(y_vs, y_ve) >= std::min(y_us, y_ue)) &&
	//	(multiply(v.s, u.e, u.s) * multiply(u.e, v.e, u.s) >= 0) &&         //跨立实验 
	//	(multiply(u.s, v.e, v.s) * multiply(v.e, u.e, v.s) >= 0));

	return EIntersectStatus::EIntersectNonVectex;
}
bool isPointInsidePolygon(type_polygon polygon2d, type_pt2d point)
{
	return false;
}
type_pt2d getCenterPoint(type_polygon polygon2d)
{
	return type_pt2d();
}
// 检测多边形是否与box相交
EPolygonStatus polygonIntersect(type_polygon polygon, Box box)
{
	bool hasIntersectHasVectex = false;
	
	// polygon-box
	const auto polygon_box = std::move(box.toPolygon2d());
	for (size_t i = 0; i < polygon.size(); i++)
	{
		Lineseg seg_1{ polygon[i],polygon[(i + 1) % polygon.size()] };
		for (size_t j = 0; j < polygon_box.size(); j++)
		{
			EIntersectStatus status = intersect(seg_1, Lineseg(polygon_box[j], polygon_box[(j + 1) % polygon_box.size()]));
			if (status == EIntersectStatus::EIntersectNonVectex)
			{
				return EPolygonStatus::Eintersect;
			}

			if (status == EIntersectStatus::EIntersectHasVectex)
			{
				hasIntersectHasVectex = true;
				break;
			}
		}
	}
	bool isBoxCenterInside = false;
	isBoxCenterInside = isPointInsidePolygon(polygon, getCenterPoint(polygon_box));
	if (!hasIntersectHasVectex)
	{
		if (isBoxCenterInside)
		{
			return EPolygonStatus::Einside;
		}
		else
		{
			return EPolygonStatus::Eexternal;
		}
	}
	// down context is all Intersect is vectex 
	//
	//bool hasSegmentParallel = false;
	for (size_t i = 0; i < polygon.size(); i++)
	{
		Lineseg seg_1{ polygon[i],polygon[(i + 1) % polygon.size()] };
		for (size_t j = 0; j < polygon_box.size(); j++)
		{
			if (isparallel(seg_1, Lineseg(polygon_box[j], polygon_box[(j + 1) % polygon_box.size()])))
			{
				bool conditionNextSeg = intersect(seg_1, Lineseg(polygon_box[(j + 1) % polygon_box.size()],
					polygon_box[(j + 2) % polygon_box.size()]))
					== EIntersectStatus::EIntersectHasVectex;
				if (conditionNextSeg)
				{
					if (isBoxCenterInside)
					{
						return EPolygonStatus::EparallelInside;
					}
					else
					{
						return EPolygonStatus::EparallelExternal;
					}
				}
				size_t lastIndex = 0;
				if ((j - 1) < 0)
				{
					lastIndex = polygon_box.size() - 1;
				}
				else
				{
					lastIndex = j - 1;
				}
				bool conditionlastSeg2 = intersect(seg_1, Lineseg(polygon_box[lastIndex] ,
					polygon_box[(j) % polygon_box.size()]))
					== EIntersectStatus::EIntersectHasVectex;
				if (conditionlastSeg2)
				{
					if (isBoxCenterInside)
					{
						return EPolygonStatus::EparallelInside;
					}
					else
					{
						return EPolygonStatus::EparallelExternal;
					}
				}

				bool conditionNextSeg3 = intersect(Lineseg(polygon[(i + 1) % polygon.size()],
					polygon[(i + 2) % polygon.size()]),
					Lineseg(polygon_box[j],polygon_box[(j + 1) % polygon_box.size()]))
					== EIntersectStatus::EIntersectHasVectex;
				if (conditionNextSeg3)
				{
					if (isBoxCenterInside)
					{
						return EPolygonStatus::EparallelInside;
					}
					else
					{
						return EPolygonStatus::EparallelExternal;
					}
				}
				if ((i - 1) < 0)
				{
					lastIndex = polygon_box.size() - 1;
				}
				else
				{
					lastIndex = i - 1;
				}
				bool conditionlastSeg4 = intersect(Lineseg(polygon[lastIndex],
					polygon[i]),
					Lineseg(polygon_box[j], polygon_box[(j + 1) % polygon_box.size()]))
					== EIntersectStatus::EIntersectHasVectex;
				if (conditionlastSeg4)
				{
					if (isBoxCenterInside)
					{
						return EPolygonStatus::EparallelInside;
					}
					else
					{
						return EPolygonStatus::EparallelExternal;
					}
				}

			}
		}
	}
	

	


}

void room_auto(type_polygon polygon_room, std::vector<Box> vec_box, type_func_constraint func_constraint)
{

}

int main(void)
{

	return 0;
}