/*
 * 2048-Like Game
 * Description:
 * A console-based game inspired by 2048, played on a 4x4 grid. The game allows players 
 * to combine tiles that are powers of 2 through sliding moves in four directions. 
 * The program includes three difficulty levels (easy, medium, hard) that influence 
 * tile movement and number generation. Players aim to reach the highest possible tile 
 * by strategically merging like-numbered tiles while avoiding grid congestion.
 */
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "mersenne-twister.h" //Include your Mersenne Twister RNG header file



using namespace std;

class Board {
private:
    static const int SIZE = 4;
    int grid[SIZE][SIZE];
    int target;

    //Helper to print a row divider
    void printRowDivider() {
        cout << string(21, '-') << endl;
    }

public:
    Board(int modeTarget) : target(modeTarget) {
        //Initialize the board to all zeros
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                grid[i][j] = 0;
            }
        }
    }

    void printBoard() {
    //Ensure consistent formatting of grid
    printRowDivider();
    for (int i = 0; i < SIZE; ++i) {
        cout << "|";
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0)
                cout << "    |"; // Empty cell
            else
                cout << setw(4) << grid[i][j] << "|"; //Align non-zero values
        }
        cout << endl;
        printRowDivider();
    }
}

bool slideLeft() {
    bool moved = false;

    //Loop through each row
    for (int i = 0; i < SIZE; ++i) {
        bool merged[SIZE] = {false}; //Track if a tile has already been merged this turn

        //Loop through each column (starting from the second column)
        for (int j = 1; j < SIZE; ++j) {
            if (grid[i][j] != 0) {
                int target = j - 1; //The target position is one space left

                //Move the tile left one space
                if (grid[i][target] == 0) {
                    grid[i][target] = grid[i][j];
                    grid[i][j] = 0;
                    moved = true;
                    continue;
                }

                //If the tile can merge with the one left of it (same value and not merged yet)
                if (grid[i][target] == grid[i][j] && !merged[target]) {
                    grid[i][target] *= 2; // Merge the two tiles
                    grid[i][j] = 0; // Clear the original tile
                    merged[target] = true; // Mark the tile as merged
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool slideRight() {
    bool moved = false;

    // Loop through each row
    for (int i = 0; i < SIZE; ++i) {
        bool merged[SIZE] = {false}; // Track merged tiles for this row

        // Iterate right-to-left to handle sliding
        for (int j = SIZE - 2; j >= 0; --j) {
            if (grid[i][j] != 0) { // If the current tile is not empty
                int target = j + 1; // The target is the next position to the right

                // Check if the target spot is empty
                if (grid[i][target] == 0) {
                    grid[i][target] = grid[i][j]; // Move tile
                    grid[i][j] = 0;              // Clear original position
                    moved = true;
                }
                // If the target spot has the same value and hasn't been merged
                else if (grid[i][target] == grid[i][j] && !merged[target]) {
                    grid[i][target] *= 2; // Merge the tiles
                    grid[i][j] = 0;      // Clear original position
                    merged[target] = true; // Mark this tile as merged
                    moved = true;
                }
            }
        }
    }

    return moved;
}






bool slideUp() {
    bool moved = false;

    //Loop through each column
    for (int j = 0; j < SIZE; ++j) {
        bool merged[SIZE] = {false}; //Track if a tile has already been merged this turn

        //Loop through each row (starting from the second row)
        for (int i = 1; i < SIZE; ++i) {
            if (grid[i][j] != 0) {
                int target = i - 1; //The target position is one space up

                //Move the tile up one space
                if (grid[target][j] == 0) {
                    grid[target][j] = grid[i][j];
                    grid[i][j] = 0;
                    moved = true;
                    continue;
                }

                //If the tile can merge with the one above it (same value and not merged yet)
                if (grid[target][j] == grid[i][j] && !merged[target]) {
                    grid[target][j] *= 2; //Merge the two tiles
                    grid[i][j] = 0; //Clear the original tile
                    merged[target] = true; //Mark the tile as merged
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool slideDown() {
    bool moved = false;

    //Loop through each column
    for (int j = 0; j < SIZE; ++j) {
        bool merged[SIZE] = {false}; //Track if a tile has already been merged this turn

        //Loop through each row (starting from the second-to-last row)
        for (int i = SIZE - 2; i >= 0; --i) {
            if (grid[i][j] != 0) {
                int target = i + 1; //The target position is one space down

                //Move the tile down one space
                if (grid[target][j] == 0) {
                    grid[target][j] = grid[i][j];
                    grid[i][j] = 0;
                    moved = true;
                    continue;
                }

                //If the tile can merge with the one below it (same value and not merged yet)
                if (grid[target][j] == grid[i][j] && !merged[target]) {
                    grid[target][j] *= 2; //Merge the two tiles
                    grid[i][j] = 0; //Clear the original tile
                    merged[target] = true; //Mark the tile as merged
                    moved = true;
                }
            }
        }
    }

    return moved;
}



void addRandomNumber(int mode) {
    //Step 1: Find all empty cells
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0) { // Identify empty spots
                emptyCells.push_back({i, j});
            }
        }
    }

    //Step 2: If no empty cells, exit
    if (emptyCells.empty()) return;

    //Step 3: Choose a random empty cell
    int randomIndex = chooseRandomNumber(1, emptyCells.size()) - 1; //Convert 1-based to 0-based
    pair<int, int> cell = emptyCells[randomIndex];

    //Step 4: Assign value (2 or 4) based on mode
    int randomValue = chooseRandomNumber(1, 10); //90% chance of 2, 10% chance of 4
    grid[cell.first][cell.second] = (randomValue > (mode == 1 ? 5 : mode == 2 ? 7 : 9)) ? 4 : 2;
}

    void transpose() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = i + 1; j < SIZE; ++j) {
                swap(grid[i][j], grid[j][i]);
            }
        }
    }

    void reverseRows() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                swap(grid[i][j], grid[i][SIZE - 1 - j]);
            }
        }
    }

    
    bool hasMoves() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] == 0) return true;
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE - 1; ++j) {
                if (grid[i][j] == grid[i][j + 1] || grid[j][i] == grid[j + 1][i])
                    return true;
            }
        }
        return false;
    }

    bool hasWon() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] == target) return true;
            }
        }
        return false;
    }
};

int main() {
    cout << "Enter random seed: " << endl;
    int seedValue;
    cin >> seedValue;
    seed(seedValue);

    char modeInput;
    int mode;

    //Loop until a valid mode is entered
    do {
        cout << "Choose game mode: Easy (E), Medium (M), or Hard (H): " << endl;
        cin >> modeInput;
        modeInput = toupper(modeInput);

        if (modeInput == 'E') mode = 1;
        else if (modeInput == 'M') mode = 2;
        else if (modeInput == 'H') mode = 3;
        else {
            cout << "Error: Invalid mode." << endl;
            mode = 0; //Reset mode to trigger the loop
        }

        //Only add a newline if the mode is valid (after a successful prompt)
        if (mode != 0) {
            cout << endl; //Add a blank line after the valid mode prompt
        }

    } while (mode == 0); //Keep looping until a valid mode is entered

    int target = (mode == 1) ? 256 : (mode == 2) ? 512 : 1024;
    Board gameBoard(target);

    gameBoard.addRandomNumber(mode);
    gameBoard.addRandomNumber(mode);

    while (true) {
    gameBoard.printBoard();

    if (gameBoard.hasWon()) {
        cout << "You win!" << endl;
        break;
    }

    if (!gameBoard.hasMoves()) {
        cout << "You lose." << endl;
        break;
    }

    cout << "Enter move: U, D, L, or R. Q to quit: " << endl << endl;
    char move;
    cin >> move;
    move = toupper(move);

    if (move == 'U') gameBoard.slideUp();
    else if (move == 'D') gameBoard.slideDown();
    else if (move == 'L') gameBoard.slideLeft();
    else if (move == 'R') gameBoard.slideRight();
    else if (move == 'Q') break;
    else {
        cout << "Error: Invalid move." << endl;
        continue;
    }

    //Generate a random number after each valid input
    gameBoard.addRandomNumber(mode);
}

    return 0;
}
