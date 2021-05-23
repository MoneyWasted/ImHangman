#include "imgui/imgui.h"
#include "Renderer.h"
#include "WordManager.hpp"
#include <atomic>
#include <optional>

#define MAX_TRIES 5
#define WHITE ImColor(255, 255, 255, 255)

bool debug = true;
Renderer* RENDERER = new Renderer;
std::optional<string> RandWord = RandomWord();

void DrawScene()
{	
	auto word = RandWord.value().c_str();

    // Handle Float to Char and Display FPS
    char buffer[64];
    int ret = snprintf(buffer, sizeof buffer, "%.f FPS", ImGui::GetIO().Framerate);
    RENDERER->DrawTextW(ImVec2(1, 1), WHITE, buffer);

	// DEBUG: Get a new word when button is pressed.
	if (debug) {
		ImGui::Begin("Debug", &debug);
		ImGui::Text("Current Word: %s", word);
		ImGui::End();
	}

	// Draw Head
	RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, WHITE);

	// Draw Body
	RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), WHITE, 10);

	// Draw Legs
	RENDERER->DrawLine(ImVec2(305, 300), ImVec2(255, 350), WHITE, 10); // Right Leg
	RENDERER->DrawLine(ImVec2(305, 300), ImVec2(355, 350), WHITE, 10); // Left Leg

	// Draw Arms
	RENDERER->DrawLine(ImVec2(305, 200), ImVec2(255, 250), WHITE, 10); // Right Arm
	RENDERER->DrawLine(ImVec2(305, 200), ImVec2(355, 250), WHITE, 10); // Left Arm

    // Draw Word
    RENDERER->DrawTextW(ImVec2(500, 200), WHITE, word);
}