#include "CAppRepository.h"

CAppRepository::~CAppRepository()
{
}

CAppRepository * CAppRepository::Instance()
{
	static CAppRepository app;
	return &app;
}

CAppRepository::CAppRepository()
{
}
