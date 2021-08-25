#include "C3DViewPortWidget.h"
#include "imgui.h"

C3DViewPortWidget::C3DViewPortWidget()
{
}

C3DViewPortWidget::~C3DViewPortWidget()
{
}

void C3DViewPortWidget::update()
{
	
	{


		ImGui::Begin("view 3d"); 


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::Image()

		ImGui::End();
	}


}
