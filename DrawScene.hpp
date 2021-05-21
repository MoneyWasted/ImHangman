#include "imgui/imgui.h"
#include "Renderer.h"

Renderer* RENDERER = new Renderer;

#define WHITE ImColor(255, 255, 255, 255)

void DrawScene()
{	
	// Draw Head
	RENDERER->DrawFilledCircle(ImVec2(200, 125), 50, 50.f, WHITE);

	// Draw Body
	RENDERER->DrawLine(ImVec2(200, 125), ImVec2(200, 300), WHITE, 10);

	// Draw Legs
	RENDERER->DrawLine(ImVec2(200, 300), ImVec2(150, 350), WHITE, 10); // Right Leg
	RENDERER->DrawLine(ImVec2(200, 300), ImVec2(250, 350), WHITE, 10); // Left Leg

	// Draw Arms
	RENDERER->DrawLine(ImVec2(200, 200), ImVec2(150, 250), WHITE, 10); // Right Arm
	RENDERER->DrawLine(ImVec2(200, 200), ImVec2(250, 250), WHITE, 10); // Left Arm
}