#pragma once

#include "imgui/imgui.h"

void SetupStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();

	style.WindowPadding = ImVec2(0, 0);
	style.WindowBorderSize = 0.f;
	style.PopupBorderSize = 0.f;
}