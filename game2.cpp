#include "game.h"
#include <iomanip>
#include <iostream>

using namespace std;

Game::Game() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            board[i][j] = '-';
        }
    }
}

void Game::printBoard() {
    cout << "------------------------------------------------";
    for(int i = 0; i < 5; i++) {
        cout << '\n' << "|";
        for(int j = 0; j < 5; j++) {
            cout << setw(5) << board[i][j] << setw(5) << " |";
        }
    }
    cout << '\n' << "------------------------------------------------" << '\n';
}

bool Game::gameOver() {
    if(CheckWin(HUMAN) || CheckWin(AI)) return true;

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(board[i][j] == '-') return false;
        }
    }

    return true;
}

bool Game::CheckWin(Player player) {
    char playerChar = (player == HUMAN) ? human : ai;

    // Check rows and columns
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++) {
            // Check horizontal
            if(board[i][j] == playerChar && board[i][j+1] == playerChar && board[i][j+2] == playerChar) return true;
            // Check vertical
            if(board[j][i] == playerChar && board[j+1][i] == playerChar && board[j+2][i] == playerChar) return true;
        }
    }

    // Check diagonals (top-left to bottom-right)
    for(int i = 0; i <= 2; i++) {
        for(int j = 0; j <= 2; j++) {
            if(board[i][j] == playerChar && board[i+1][j+1] == playerChar && board[i+2][j+2] == playerChar) return true;
        }
    }

    // Check diagonals (top-right to bottom-left)
    for(int i = 0; i <= 2; i++) {
        for(int j = 2; j < 5; j++) {
            if(board[i][j] == playerChar && board[i+1][j-1] == playerChar && board[i+2][j-2] == playerChar) return true;
        }
    }

    return false;
}

int Game::score() {
    if(CheckWin(HUMAN)) return 10;
    if(CheckWin(AI)) return -10;
    return 0; // Draw
}

Move Game::minimax(char AIboard[5][5], int alpha, int beta, bool isMaximizing) {
    if(gameOver()) {
        return { -1, -1 }; // Indicate no move
    }

    int bestMoveScore = isMaximizing ? -1000 : 1000;
    Move bestMove = { -1, -1 };

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(AIboard[i][j] == '-') {
                AIboard[i][j] = isMaximizing ? human : ai;
                int currentMoveScore = isMaximizing ? minsearch(AIboard, alpha, beta) : maxsearch(AIboard, alpha, beta);

                if (isMaximizing) {
                    if(currentMoveScore > bestMoveScore) {
                        bestMoveScore = currentMoveScore;
                        bestMove.x = i;
                        bestMove.y = j;
                    }
                    alpha = max(alpha, bestMoveScore);
                } else {
                    if(currentMoveScore < bestMoveScore) {
                        bestMoveScore = currentMoveScore;
                        bestMove.x = i;
                        bestMove.y = j;
                    }
                    beta = min(beta, bestMoveScore);
                }

                AIboard[i][j] = '-';

                if(beta <= alpha) return bestMove; // Alpha-beta pruning
            }
        }
    }

    return bestMove;
}

int Game::maxsearch(char AIboard[5][5], int alpha, int beta) {
    if(gameOver()) return score();

    int bestMoveScore = -1000;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(AIboard[i][j] == '-') {
                AIboard[i][j] = human;
                int tempMoveScore = minsearch(AIboard, alpha, beta);
                AIboard[i][j] = '-';
                bestMoveScore = max(bestMoveScore, tempMoveScore);
                alpha = max(alpha, bestMoveScore);
                if(beta <= alpha) return bestMoveScore; // Alpha-beta pruning
            }
        }
    }

    return bestMoveScore;
}

int Game::minsearch(char AIboard[5][5], int alpha, int beta) {
    if(gameOver()) return score();

    int bestMoveScore = 1000;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(AIboard[i][j] == '-') {
                AIboard[i][j] = ai;
                int tempMoveScore = maxsearch(AIboard, alpha, beta);
                AIboard[i][j] = '-';
                bestMoveScore = min(bestMoveScore, tempMoveScore);
                beta = min(beta, bestMoveScore);
                if(beta <= alpha) return bestMoveScore; // Alpha-beta pruning
            }
        }
    }

    return bestMoveScore;
}

void Game::play() {
    int turn = 0;
    printBoard();
    while(!CheckWin(HUMAN) && !CheckWin(AI) && !gameOver()) {
        if(turn % 2 == 0) {
            getHumanMove();
            if(CheckWin(HUMAN)) {
                cout << "Human Player Wins" << endl;
                break;
            }
            turn++;
            printBoard();
        } else {
            cout << endl << "Computer Player Move:" << endl;
            Move AImove = minimax(board, -1000, 1000, false);
            board[AImove.x][AImove.y] = ai;
            if(CheckWin(AI)) {
                cout << "Computer Player Wins" << endl;
                break;
            }
            turn++;
            printBoard();
        }
    }
    if (!CheckWin(HUMAN) && !CheckWin(AI)) {
        cout << "It's a draw!" << endl;
    }
}

void Game::getHumanMove() {
    int x = -1, y = -1; // Initialize x and y
    while(x < 0 || x > 5 || y < 0 || y > 5) {
        cout << "Enter your move in coordinate form, ex: (1,5)." << endl;
        cout << "Your Move: ";
        char c;
        string restofline;
        cin >> c >> c;  // Read '(' and ','
        x = c - '0' - 1;  // Convert character to integer and adjust for 0-based index
        cin >> c >> c;  // Read ',' and ')'
        y = c - '0' - 1;  // Convert character to integer and adjust for 0-based index
        getline(cin, restofline); // Get garbage characters after move

        if(x < 0 || x > 5 || y < 0 || y > 5 || board[x][y] != '-') {
            cout << "Invalid move. Try again." << endl;
            x = -1; // Reset x and y
            y = -1;
        }
    }
    board[x][y] = human;
}
