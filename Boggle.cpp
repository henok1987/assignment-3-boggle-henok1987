#include "Boggle.h"
#include <iostream>
#include <fstream>
#include "Dictionary.h"

using namespace std;


Boggle::Boggle() {
    // Load "dictionary.txt" into dict
    dict.LoadDictionaryFile("dictionary.txt");
}
Boggle::Boggle(string filename) {
    // Constructor to Load filename into dict
    dict.LoadDictionaryFile(filename);
}
// Set the board configuration
void Boggle::SetBoard(string Board[BOARD_SIZE][BOARD_SIZE]) {

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            this->board[i][j] = Board[i][j];
        }
    }
}
// Get the dictionary
Dictionary Boggle::GetDictionary() {
    return dict;
}
// Return the dictionary
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

void Boggle::SolveBoard(bool printBoard, ostream& output) {
    // Print the board
    if (printBoard) {
        PrintBoard(output);
    }
    // Initialize visited array
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            visited[i][j] = 0;
        }
    }
    // Iterate through each cell
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            visited[i][j] = 0;
            SolveBoardHelper(i, j, "", visited, output);
        }
    }
}
void Boggle::SolveBoardHelper(int row, int col, string word, bool Visited[BOARD_SIZE][BOARD_SIZE], ostream &output) {
        //Mark the current cell as visited
        visited[row][col] = 1;
        word += board[row][col];

        //If the word is in the dictionary and not already found, add it to wordsFound
        if (dict.IsWord(word) && !wordsFound.IsWord(word)) {
            wordsFound.AddWord(word);
            output << word << endl; // Print the word to the output
        }
        //Recursively searching in all directions
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (row + i >= 0 && row + i < BOARD_SIZE && col + j >= 0 && col + j < BOARD_SIZE &&
                    !visited[row + i][col + j]) {
                    SolveBoardHelper(row + i, col + j, word, visited, output);
                }
            }
        }
        visited[row][col] = 0; //Mark the current cell as not visited
    }

void Boggle::PrintBoard(ostream &output) {
    //Print the current board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            output << board[i][j] << " ";
        }
        output << endl;
    }
}
//Save the found words to a file
void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

