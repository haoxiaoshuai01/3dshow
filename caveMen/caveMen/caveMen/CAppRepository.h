#pragma once
enum EAfter
{
	normal,
	lightLess

};
class CAppRepository
{
public:
	
	~CAppRepository();
	static CAppRepository *Instance();

	EAfter aftertreatmentType;
private:
	CAppRepository();
};

