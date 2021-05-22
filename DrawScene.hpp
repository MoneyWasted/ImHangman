#include "imgui/imgui.h"
#include "Renderer.h"
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

Renderer* RENDERER = new Renderer;
#define WHITE ImColor(255, 255, 255, 255)
using namespace std;

string RandomWord()
{
    string line;
    vector<string> lines;

    // Set random seed using current time
    srand(time(0));

    // Input file stream
    ifstream file("words.txt");

    // Count number of total lines in the file and store the lines in the string vector
    int total_lines = 0;
    while (getline(file, line))
    {
        total_lines++;
        lines.push_back(line);
    }

    // Generate a random number between 0 and count of total lines
    int random_number = rand() % total_lines;

    // Fetch the line where line index (starting from 0) matches with the random number
    return lines[random_number];
}

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

    // Draw Word
    RENDERER->DrawTextW(ImVec2(500, 200), WHITE, RandomWord().c_str());
}