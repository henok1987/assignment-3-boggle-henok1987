#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    Boggle();  // load "dictionary.txt" into dict
    explicit Boggle(string filename);  // load filename into dict

    // Sets the board configuration
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    // Solves the Boggle board. If 'printBoard' is true, the board will be printed.
    void SolveBoard(bool printBoard, ostream& output);

    // Saves all the words from the last solve to the given 'filename'.
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    // Retrieves the dictionary used by the Boggle game.
    Dictionary GetDictionary();

    // Retrieves the words found in the last solve.
    Dictionary WordsFound();

private:
    Dictionary dict; // Dictionary object to store the words
    Dictionary wordsFound; // Dictionary object to store found words
    string board[BOARD_SIZE][BOARD_SIZE]; // The Boggle game board
    bool visited[BOARD_SIZE][BOARD_SIZE]{}; // Tracks visited cells in the Boggle board

    // Prints the current board configuration to the provided output stream.
    void PrintBoard(ostream& output);

    // Recursive function to find words on the Boggle board.
    void SolveBoardHelper(int row, int col, string word, bool visited[BOARD_SIZE][BOARD_SIZE], ostream& output);
};

#endif //BOGGLE_BOGGLE_H
