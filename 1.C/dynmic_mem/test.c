#include <stdio.h>
#include<stdlib.h>
int** generateBoard() {
    int board[N][M], i, j , fillNum;
    Boolean exists = True;
    // initilize seed
    srand(time(NULL));
    // fill up..
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            exists = True;
            while(exists) {
                fillNum = rand()%MAX_RANGE + 1; // limit up to MAX_RANGE
                if(beenAdded(board, fillNum) == Exist) {
                    continue;
                } else {
                    board[i][j] = fillNum;
                    exists = False;
                }
            }
        }
    }
    return board;
}
