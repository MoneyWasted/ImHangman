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

int HandleGuess(char guess, string secretword, string& guessword)
{
    int i;
    int matches = 0;
    int len = secretword.length();
    for (i = 0; i < len; i++)
    {
        // Did we already match this letter in a previous guess?
        if (guess == guessword[i]) return 0;

        // Is the guess in the word?
        if (guess == secretword[i])
        {
            guessword[i] = guess;
            matches++;
        }
    }
    return matches;
}