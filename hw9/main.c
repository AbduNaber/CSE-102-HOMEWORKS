#include <stdio.h>
#include "util.h"

int main(){
    
    block_t ***board;
    init_board(board);
    printf("%d",board[0][0][0].type);

   // draw_board(board,snake,2);

    // free board
   for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);

    return 0;
}
