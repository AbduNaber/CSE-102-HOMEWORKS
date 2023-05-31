#include <stdio.h>
#include "util.h"

int main(){
<<<<<<< HEAD
    block_t ***board =init_board(); ;
   
    play(board);   
     
   
=======
    
    block_t ***board;
    init_board(board);
    printf("%d",board[0][0][0].type);

   // draw_board(board,snake,2);
>>>>>>> ac3247a0f6e7da976a9306ae6cdb552715b0caaa

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
