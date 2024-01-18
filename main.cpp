/************************************************************************************************
* This program replicates the game Rush Hour. The objective of the game is to make the 'R' car
* be next to the exit by moving cars around the board. To move a car, the user will enter a
* three-character sequence, which instructs the car to move (if possible or as much as possible).
* Otherwise, the user could quit the game.
* Class: CS 141, Fall 2023
* System: Zybook Lab
* @author Elizabeth Ng
* @version October 8, 2023
************************************************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

/*
 * Description: Displays the board with the borders and the equal sign.
 * Input: board1 (a 2D array AKA a board with cars on it)
 * Output: void (just prints)
 */
void displayBoard(char board1[6][6]) {
    cout << "--------" << endl;
    for (int a = 0; a < 6; ++a) {
        for (int b = 0; b < 6; ++b) {
            if (b == 0) {
                cout << "|";
            }
            cout << board1[a][b];
        }

        if (a == 2) {
            cout << "=" << endl;
        }
        else {
            cout << "|" << endl;
        }
    }
    cout << "--------" << endl;
}

/*
 *  Description: Checks the user's car input. Verifies whether or not the car exists on the board.
 *  Inputs: board2 (a 2D array AKA a board with cars on it), car1 (the car that the user wants to move)
 *  Output: carPresence (true, if the car exists. Otherwise, false)
 */
bool carExistence(char board2[6][6], char car1) {
    bool carPresence = true;
    int carCounter = 0;

    for (int c = 0; c < 6; ++c) {
        for (int d = 0; d < 6; ++d) {
            if (board2[c][d] == car1) {
                carCounter += 1;
            }
        }
    }

    if (carCounter == 0) {
        carPresence = false;
    }

    return carPresence;
}

int main()
{
    ifstream inFS; // Input file stream
    string fileString;
    string fileName;

    char myBoard[6][6]; // Declared a 2D array (main game board)
    char tempBoard[6][6]; // Serves as a temp 2D array

    // Prompt the user for a filename (AKA a board to use)
    cout << "Enter filename: ";
    cin >> fileName;

    inFS.open(fileName);

    if (!inFS.is_open()) {
        cout << "Could not open file board.txt." << endl;
        return 1;
    }

    inFS >> fileString;
    while (!inFS.fail()) {
        // Initializes myBoard by using the file
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (fileString.at(j) == 45) {
                    myBoard[i][j] = '.';
                }
                else {
                    myBoard[i][j] = fileString.at(j);
                }
            }

            inFS >> fileString;
        }

        bool firstQuit = false;

        while (myBoard[2][5] != 'R') {
            // Display board
            displayBoard(myBoard);

            // Prompt the user for input
            // Either "Q" or a three-character sequence
            string userInput;
            cout << "Enter next move (or Q to quit): ";
            cin >> userInput;

            // The game will quit if the user doesn't want to play the game at all
            if (userInput == "Q") {
                firstQuit = true;
                break;
            }

            char car = userInput.at(0);
            int numMoves = userInput.at(1) - '0';
            char direction = userInput.at(2);

            // Makes a lowercase car input become uppercase
            if (int(car) >= 97) {
                car = char(int(car) - 32);
            }

            // Checks if the car that the user wants to move is on the board
            bool checkCar = carExistence(myBoard, car);

            // Car exists
            if (checkCar == true) {
                while (numMoves > 0) {
                    int numCarParts = 0; // Keeps track of the number of parts the car has

                    // Copies everything, except for the car that the user wants to move, from myBoard to tempBoard
                    // '.' takes the place of the car that the user wants to move in tempBoard
                    for (int m = 0; m < 6; ++m) {
                        for (int n = 0; n < 6; ++n) {
                            if (myBoard[m][n] == car) {
                                tempBoard[m][n] = '.';
                                numCarParts += 1;
                            }
                            else {
                                tempBoard[m][n] = myBoard[m][n];
                            }
                        }
                    }

                    int tempNumCarParts = 0; // Will be compared with numCarParts

                    // Moves car
                    for (int row = 0; row < 6; ++row) {
                        for (int col = 0; col < 6; ++col) {
                            if (myBoard[row][col] == car) {
                                // Moves car to the left by only one space
                                if (direction == 'L' || direction == 'l') {
                                    if (col == 0) {
                                        continue; // Makes sure the car doesn't move to the left if it's in column 0 (or the edge of the board)
                                    }
                                    else {
                                        if (tempBoard[row][col - 1] == '.') {
                                            tempBoard[row][col - 1] = car;
                                            tempNumCarParts += 1;
                                        }
                                    }
                                }
                                    // Moves car to the right by only one space
                                else if (direction == 'R' || direction == 'r') {
                                    if (col == 5) {
                                        continue; // Makes sure the car doesn't move to the right if it's in column 5 (or the edge of the board)
                                    }
                                    else {
                                        if (tempBoard[row][col + 1] == '.') {
                                            tempBoard[row][col + 1] = car;
                                            tempNumCarParts += 1;
                                        }
                                    }
                                }
                                    // Moves car upwards by only one space
                                else if (direction == 'U' || direction == 'u') {
                                    if (row == 0) {
                                        continue; // Makes sure the car doesn't move up if it's in row 0 (of the edge of the board)
                                    }
                                    else {
                                        if (tempBoard[row - 1][col] == '.') {
                                            tempBoard[row - 1][col] = car;
                                            tempNumCarParts += 1;
                                        }
                                    }
                                }
                                    // Moves car downards by only one space
                                else if (direction == 'D' || direction == 'd') {
                                    if (row == 5) {
                                        continue; // Makes sure the car doesn't move down if it's in row 5 (or the edge of the board)
                                    }
                                    else {
                                        if (tempBoard[row + 1][col] == '.') {
                                            tempBoard[row + 1][col] = car;
                                            tempNumCarParts += 1;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Checks if all parts of the car were able to move
                    if (numCarParts == tempNumCarParts) {
                        // Updates myBoard by copying tempBoard to myBoard
                        for (int s = 0; s < 6; ++s) {
                            for (int t = 0; t < 6; ++t) {
                                myBoard[s][t] = tempBoard[s][t];
                            }
                        }
                        numMoves -= 1;
                    }
                    else {
                        break; // Not every part of the car was able to move. Exit this loop to prompt the user for a new input if 'R' is not next to the exit
                    }
                }

            }
                // Car doesn't exist
            else {
                cout << endl;
                cout << "That car is not on the board." << endl;
                continue; // Continue with the next iteration of the loop AKA prompt the user with a new input if 'R' is not next to the exit
            }
        }

        // The user entered "Q" for their first input, so the game immediataly quits
        if (firstQuit == true) {
            break;
        }

        // 'R' is by the exit, so the user wins, and the game quits
        if (myBoard[2][5] == 'R') {
            displayBoard(myBoard);
            cout << "You win! Congratulations!" << endl;
            break;
        }

    }

    if (!inFS.eof()) {
        cout << "Input failure before reaching end of file." << endl;
    }

    // Done with file, so close it
    inFS.close();

    return 0;
}
