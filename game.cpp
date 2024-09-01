#include <iostream>
#include <sstream>
#include <iomanip>
#include "game.h"

using namespace std;

Game::Game() {
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			board[i][j] = '-';
		}
	}
}

void Game::printBoard() {
	cout << "-------------------";
	for(int i = 0; i < 5; i++) {
		cout << '\n' << "|";
		for(int j = 0; j < 5; j++) {
			cout << setw(5) << board[i][j] << setw(5) << " |";
		}
	}
	cout << '\n' << "-------------------" << '\n';
}

bool Game::gameOver() {
	if(CheckWin(HUMAN)) return true;
	else if(CheckWin(AI)) return true;

	bool emptySpace = false;
	for(int i = 0; i < 5; i++) {
		if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-' || board[i][3] == '-' || board[i][4] == '-')
			emptySpace = true;
	}
	return !emptySpace;
}

bool Game::CheckWin(Player player) {
	char playerChar;
	if(player == HUMAN) playerChar = human;
	else playerChar = ai;

	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 3; j++) {
			//check horizontals
			if(board[i][j] == playerChar && board[i][j+1] == playerChar 
				&& board[i][j+2] == playerChar){
					return true;
				}
			//check verticals
			if(board[i][j] == playerChar && board[i+1][j] == playerChar 
				&& board[i+2][j] == playerChar){
					return true;
				}
		}
	}

	//Check diagonals (top-left to bottom-right)
	for(int i = 0; i <= 2; i++) {
        for(int j = 0; j <= 2; j++) {
            if(board[i][j] == playerChar && board[i+1][j+1] == playerChar
               && board[i+2][j+2] == playerChar) {
                return true;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for(int i = 0; i <= 2; i++) {
        for(int j = 2; j < 5; j++) {
            if(board[i][j] == playerChar && board[i+1][j-1] == playerChar
               && board[i+2][j-2] == playerChar) {
                return true;
            }
        }
    }

	return false;
}

int Game::score() {
	if(CheckWin(HUMAN)) { return 10; }
	else if(CheckWin(AI)) { return -10; }
	return 0; // draw
}

Move Game::minimax(char AIboard[3][3]) { 
	int bestMoveScore = 100; // -100 is arbitrary
	Move bestMove;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMoveScore = maxsearch(AIboard);
				if(tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMove;
}

int Game::maxsearch(char AIboard[3][3]) {
	if(gameOver()) return score();
	Move bestMove;

	int bestMoveScore = -1000;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = human;
				int tempMoveScore = minsearch(AIboard);
				if(tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

int Game::minsearch(char AIboard[3][3]) {
	if(gameOver()) return score();
	Move bestMove;

	int bestMoveScore = 1000; 
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMove = maxsearch(AIboard);
				if(tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

void Game::getHumanMove() {
	int x, y = -1; // arbitrary assignment to init loop
	while(x < 0 || x > 2 || y < 0 || y > 2) {
		// Loop until a valid move is entered
		cout << "Enter your move in coordinate form, ex: (1,3)." << endl;
		cout << "Your Move: ";
		char c;
		string restofline;
		cin >> c >> c;
		x = c - '0' - 1;
		cin >> c >> c;
		y = c - '0' - 1;
		getline(cin, restofline); // get garbage chars after move
	}
	board[x][y] = human;
}

void Game::play() {
	int turn = 0;
	printBoard();
	while(!CheckWin(HUMAN) && !CheckWin(AI) && !gameOver()) {
		// human move
		if(turn % 2 == 0) {
			getHumanMove();
			if(CheckWin(HUMAN)) cout << "Human Player Wins" << endl;
			turn++;
			printBoard();
		} else {
			cout << endl << "Computer Player Move:" << endl;
			Move AImove = minimax(board);
			board[AImove.x][AImove.y] = ai;
			if(CheckWin(AI)) cout << "Computer Player Wins" << endl;
			turn++;
			printBoard();
		}
	}
}