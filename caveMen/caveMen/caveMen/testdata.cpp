#include "testdata.h"

namespace Testdata
{
	std::vector<rayINData> rayINDatas = { 
		{vec3(0,0,0),vec3(0,0,1),vec3(-1,-1,3), vec3(0, 1, 3), vec3(1, -1, 3)},//ok
	{vec3(0,0,0),vec3(0,0,1),vec3(-1,1,3), vec3(0, 2, 3), vec3(1, 1, 3)},//false,
		{vec3(0,0,0),vec3(0,0,1),vec3(-1,-1,3), vec3(0, 1, 3), vec3(1, -1, 0)},//ok
		{vec3(0,0,0),vec3(0,0,1),vec3(0,0,3), vec3(1, 1, 3), vec3(2, 0, 0)},//ok
		{vec3(0,0,0),vec3(0,0,1),vec3(0,1,3), vec3(1, 1, 3), vec3(2, 0, 0)}//false
	};
};

