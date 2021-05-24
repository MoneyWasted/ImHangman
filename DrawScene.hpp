#include "imgui/imgui.h"
#include "Renderer.h"
#include "WordManager.hpp"
#include <atomic>
#include <optional>
#include <iostream>

#define MAX_TRIES 5
#define WHITE ImColor(255, 255, 255, 255)

bool debug = true;
bool game = true;

Renderer* RENDERER = new Renderer;
std::optional<string> RandWord = RandomWord();

const char* message = "";
char letter;

// Initialize the secret word with the * character.
string HiddenWord(RandWord.value().length(), '*');

void DrawScene()
{
	int NumWrongGuesses = 0;
	auto word = RandWord.value();

	// Handle Float to Char and Display FPS
	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%.f FPS", ImGui::GetIO().Framerate);
	RENDERER->DrawTextW(ImVec2(1, 1), WHITE, buffer);

	// DEBUG: Display Debug Info about the Game.
	if (debug) {
		ImGui::Begin("Debug", &debug, ImGuiWindowFlags_NoResize);
		ImGui::SetWindowSize(ImVec2(250, 100));
		ImGui::Text("Current Word: %s", word);
		ImGui::Text("Current Number of Guesses: %i", NumWrongGuesses);
		ImGui::End();
	}

	// Draw the Bottom where all the text goes.
	ImGui::Begin("Game", &game, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowSize(ImVec2(1020, 100));
	ImGui::SetWindowPos(ImVec2(0, 576));
	ImGui::Text(message);
	ImGui::End();

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

	// Key Press Loop
	for (letter = 'A'; letter <= 'Z'; letter++) {
		// If a key 'A' through 'Z' is pressed.
		if (ImGui::IsKeyPressed(letter))
		{
			// iterate over the characters in word and guess
			for (size_t i = 0; i < sizeof(word.c_str()); i++)
			{
				if (word.c_str()[i] == tolower(letter))
				{
					HiddenWord[i] = word[i];  // if the characters match at position i, update the underscore.
					message = "You found a letter! Isn't that exciting!";
					break;
				}
				else
				{
					message = "Whoops! That letter isn't in there!";
				}
			}
		}
	}

	RENDERER->DrawTextW(ImVec2(500, 200), WHITE, HiddenWord.c_str());
}