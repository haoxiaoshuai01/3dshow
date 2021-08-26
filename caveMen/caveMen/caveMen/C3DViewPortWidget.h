#pragma once
#include "CWidget.h"
#include "imgui.h"
#include "imgui_internal.h"
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
	unsigned int textureID;
};

