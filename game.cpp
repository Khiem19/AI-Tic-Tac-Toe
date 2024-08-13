#include <iostream>
#include <iomanip>

#include "game.h"

using namespace std;

Game::Game() {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
        
    }
}

void Game::printBoard() {
    cout << "-----------------------";
    for (int i = 0; i < 3; i++){
        cout << '\n' << "|";
        for (int j = 0; j < 3; j++)
        {
            cout << setw(3) << board[i][j] << setw(3) << " |";
        }
        
    }
    cout << "\n ----------------------- \n";
}

bool Game::gameOver() {
    if (CheckWin(HUMAN)) return true;
    else if (CheckWin(AI)) return true;

    bool emptySpace = false;
    for (int i = 0; i < 3; i++){
        if(board[i][0] == '-' && board[i][1] == '-' && board[i][2] == '-')
            emptySpace = true;
    }
    return !emptySpace;
}

bool Game::CheckWin(Player player) {
    char Playerchar;
    if(player == HUMAN) Playerchar = human;
    else Playerchar = ai;

    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == Playerchar && board[i][1] == Playerchar && board[i][2] == Playerchar)
            return true;
        if (board[0][i] == Playerchar && board[1][i] == Playerchar && board[2][i] == Playerchar)
			return true;
    }

    if (board[0][0] == Playerchar && board[1][1] == Playerchar && board[2][2] == Playerchar) {
        return true;
    } else if (board[2][0] == Playerchar && board[1][1] == Playerchar && board[0][2] == Playerchar) {
        return true;
    }

    return false;
}

int Game::score() {
    if (CheckWin(HUMAN)) return 10;
    if (CheckWin(AI)) return -10;
    return 0;
}

Move Game::minimax(char AIboard[3][3]){
    int bestMoveScore = 100;
    Move bestMove;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (AIboard[i][j] == '-') {
                AIboard[i][j] = ai;
                int tempMoveScore = maxsearch(AIboard);
                if(tempMoveScore <= bestMoveScore){
                    bestMoveScore = tempMoveScore;
                    bestMove.row = i;
                    bestMove.col = j;
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

    int BestMoveScore = -1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (AIboard[i][j] == '-') {
                int tempMoveScore = minsearch(AIboard);
                if (tempMoveScore >= BestMoveScore) {
                    BestMoveScore = tempMoveScore;
                    bestMove.row = i;
                    bestMove.col = j;
                }
                AIboard[i][j] = '-';
            }
            
        }
        
    }
    return BestMoveScore;
}

int Game::minsearch(char AIboard[3][3]) {
    if(gameOver()) return score();
    Move bestMove;

    int BestMoveScore = 1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (AIboard[i][j] == '-') {
                int tempMoveScore = maxsearch(AIboard);
                if (tempMoveScore <= BestMoveScore) {
                    BestMoveScore = tempMoveScore;
                    bestMove.row = i;
                    bestMove.col = j;
                }
                AIboard[i][j] = '-';
            }
            
        }
        
    }
    return BestMoveScore;
}

