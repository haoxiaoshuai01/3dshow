#pragma once
#include "dataStruct.h"
struct rayINData
{
	vec3 o;
	vec3 dir;
	vec3 point1;
	vec3 point2;
	vec3 point3;
};
namespace Testdata
{
	extern std::vector<rayINData> rayINDatas;
};

