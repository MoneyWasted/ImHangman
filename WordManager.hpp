#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <mutex>

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