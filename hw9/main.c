#include <stdio.h>
#include "util.h"

int main(){
    block_t ***board =init_board(); ;
    printf("%c",board[0][0][0].type);
    snake_t snake[2];
    snake[0].col = 0;
    snake[0].row = 1;
    snake[1].col = 0;
    snake[1].row = 0;

    
    
   // draw_board(board,snake,2);

    // free board
   /* for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);*/

    return 0;
}
