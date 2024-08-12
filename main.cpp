#include <iostream>
#include <vector>

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

struct Move {
    int row;
    int col;
};

void Board(const vector<vector<char>>& board) {
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            cout << board[i][j] << endl;
        }
    }
    cout << endl;
}

bool isFull(const vector<vector<char>>& board){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(board[i][j] != EMPTY)
            return false;
        }
    }
    return true;
}

bool isWin(const vector<vector<char>>& board, char player) {
    for(int i = 0; i < 3; ++i){
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

vector<Move> AvailableMove(const vector<vector<char>>& board){
    vector<Move> moves;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == EMPTY){
                moves.push_back({i,j});
            }
        }
    }
    return moves;
}