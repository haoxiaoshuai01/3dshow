#pragma once
class CWidget
{
public:
	CWidget();
	virtual ~CWidget();
	virtual void update() = 0;
};

