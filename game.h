#include <iostream>

using namespace std;

const char human = 'X';
const char ai = 'O';

enum Player {HUMAN, AI};

struct Move {
    int x;
    int y;
};

class Game {
    char board[5][5];

    public:
        Game();

        void printBoard();

        bool gameOver();

        bool CheckWin(Player player);

        void play();

        void getHumanMove();

        int score();

        Move minimax(char AIboard[5][5], int alpha, int beta, bool isMaximizing);

        int minsearch(char AIboard[5][5], int alpha, int beta);

        int maxsearch(char AIboard[5][5], int alpha, int beta);
};
