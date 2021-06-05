#pragma once

#include <Windows.h>
#include <wincrypt.h>
#include "imgui/imgui.h"

class Renderer {
public:
    bool OnScreen(ImVec2 coords);
    void DrawLine(ImVec2 dst, ImVec2 src, ImColor col, int thickness);
    void DrawText(ImVec2 pos, ImColor col, const char* text);
    void DrawFilledCircle(ImVec2 pos, float radius, float segments, ImColor col);
    bool IsFullscreen(HWND windowHandle);
    ImDrawList* GetDrawList();
    ImVec2 GetWindowSize();
};