#include <atomic>
#include <optional>
#include <iostream>
#include <algorithm>

#include "imgui/imgui.h"
#include "Renderer.h"
#include "WordManager.hpp"

#define MAX_TRIES 5
#define WHITE ImColor(255, 255, 255, 255)
#define RED ImColor(255, 0, 0, 255)
#define GREEN ImColor(0, 255, 0, 255)

bool debug = true;
bool game = true;

Renderer* RENDERER = new Renderer;
optional<string> RandWord = RandomWord();

const char* message = "";
char letter;
size_t found;
int NumWrongGuesses = 0;
vector<char> guesses;

// Initialize the secret word with the * character.
string HiddenWord(RandWord.value().length(), '*');

void DrawScene()
{
	bool wrong = false;
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

	// Key Press Loop
	for (letter = 'A'; letter <= 'Z'; letter++) {
		// If a key 'A' through 'Z' is pressed.
		if (ImGui::IsKeyPressed(letter))
		{
			// Iterate over the characters in word and guess
			for (size_t i = 0; i < sizeof(word.c_str()); i++)
			{
				if (word.c_str()[i] == tolower(letter))
				{
					HiddenWord[i] = word[i];  // If the characters match at position i, update the underscore.
					message = "You found a letter! Isn't that exciting!";
					wrong = false;
					guesses.push_back(letter);
					break;
				}
				else
				{
					wrong = true;
					message = "Whoops! That letter isn't in there!";
					guesses.push_back(letter);
				}
			}
		}
	}

	if (wrong) {
		NumWrongGuesses++;
	}

	if (HiddenWord == word.c_str())
	{
		NumWrongGuesses = 0;
		message = "You Won!";
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, GREEN);     // Head
		RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), GREEN, 10); // Body
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(255, 350), GREEN, 10); // Right Leg
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(355, 350), GREEN, 10); // Left Leg
		RENDERER->DrawLine(ImVec2(305, 200), ImVec2(255, 250), GREEN, 10); // Right Arm
		RENDERER->DrawLine(ImVec2(305, 200), ImVec2(355, 250), GREEN, 10); // Left Arm
	}

	switch (NumWrongGuesses)
	{
	case 1:
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, WHITE); // Head
		break;
	case 2:
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, WHITE);     // Head
		RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), WHITE, 10); // Body
		break;
	case 3:
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, WHITE);     // Head
		RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), WHITE, 10); // Body
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(255, 350), WHITE, 10); // Right Leg
		break;
	case 4:
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, WHITE);     // Head
		RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), WHITE, 10); // Body
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(255, 350), WHITE, 10); // Right Leg
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(355, 350), WHITE, 10); // Left Leg
		break;
	case 5:
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, WHITE);     // Head
		RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), WHITE, 10); // Body
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(255, 350), WHITE, 10); // Right Leg
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(355, 350), WHITE, 10); // Left Leg
		RENDERER->DrawLine(ImVec2(305, 200), ImVec2(255, 250), WHITE, 10); // Right Arm
		break;
	case 6:
		RENDERER->DrawFilledCircle(ImVec2(305, 125), 50, 50.f, RED);     // Head
		RENDERER->DrawLine(ImVec2(305, 125), ImVec2(305, 300), RED, 10); // Body
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(255, 350), RED, 10); // Right Leg
		RENDERER->DrawLine(ImVec2(305, 300), ImVec2(355, 350), RED, 10); // Left Leg
		RENDERER->DrawLine(ImVec2(305, 200), ImVec2(255, 250), RED, 10); // Right Arm
		RENDERER->DrawLine(ImVec2(305, 200), ImVec2(355, 250), RED, 10); // Left Arm
		message = "You have lost!";
		break;
	default:
		message = "Press a key to get started.";
		break;
	}

	RENDERER->DrawTextW(ImVec2(450, 200), WHITE, HiddenWord.c_str());
}