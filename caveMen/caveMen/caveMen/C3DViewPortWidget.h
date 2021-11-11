#pragma once
#include "CWidget.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <iostream>
#include <functional>

class C3DViewPortWidget :
	public CWidget
{
public:
	C3DViewPortWidget();
	~C3DViewPortWidget();
	void setLayout();
	void ShowExampleAppDockSpace(bool * p_open);
	void update();
	ImGuiID dockspace_id;
	ImVec2 mouseRelativePos;
	unsigned int *textureID;
	bool beginMove = false;
	std::function<void()> moveFunction = nullptr;
	
};

