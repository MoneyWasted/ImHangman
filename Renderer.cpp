#include "Renderer.h"

bool Renderer::OnScreen(ImVec2 coords)
{
    if (coords.x < 0.1f || coords.y < 0.1 || coords.x > this->GetWindowSize().x || coords.y > this->GetWindowSize().y)
    {
        return false;
    }
    else 
    {
        return true;
    }
}

void Renderer::DrawLine(ImVec2 dst, ImVec2 src, ImColor col, int thickness)
{
    if (this->OnScreen(dst) && this->OnScreen(src))
    {
        this->GetDrawList()->AddLine(src, dst, col, thickness);
    }
}

void Renderer::DrawText(ImVec2 pos, ImColor col, const char* text)
{
    this->GetDrawList()->AddText(pos, col, text, 0);
}

void Renderer::DrawFilledCircle(ImVec2 pos, float radius, float segments, ImColor col)
{
    this->GetDrawList()->AddCircleFilled(pos, radius, col, segments);
}

ImDrawList* Renderer::GetDrawList() {
    return ImGui::GetForegroundDrawList();
}

bool Renderer::IsFullscreen(HWND windowHandle)
{
    MONITORINFO monitorInfo = { 0 };
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

    RECT windowRect;
    GetWindowRect(windowHandle, &windowRect);

    return windowRect.left == monitorInfo.rcMonitor.left &&
           windowRect.right == monitorInfo.rcMonitor.right &&
           windowRect.top == monitorInfo.rcMonitor.top &&
           windowRect.bottom == monitorInfo.rcMonitor.bottom;
}

ImVec2 Renderer::GetWindowSize()
{
    RECT rect;
    HWND hwnd = GetActiveWindow();
    if (GetWindowRect(hwnd, &rect))
    {
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (this->IsFullscreen(hwnd))
        {
            return ImVec2(width, height);
        }
        return ImVec2((width - 17), (height - 35));
    }
    return ImVec2(0, 0);
}