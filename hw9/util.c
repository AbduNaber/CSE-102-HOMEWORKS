#include "util.h"

block_t *** init_board(){
    srand(time(NULL));
    
    
    block_t ***board = (block_t ***)malloc(sizeof(block_t **) * ROW);

    int i,j;
    for(i = 0; i < ROW; i++){

        board[i] = (block_t **)malloc(sizeof(block_t *) * COL);

        for(j=0;j< COL ; j++){
        board[i][j]= (block_t*)malloc(sizeof(sizeof(block_t)));
        // default block is empty block
        board[i][j][0].type = 'e';
        board[i][j][0].value = 0;
        }

    }
    // create obstacle block max obstacle number is 3 min is 1
    int obstacle_num = rand() % 3 + 1;
    printf("obstacle_num: %d\n", obstacle_num);
    int obstacle_row, obstacle_col,obstacle_height;

    for(i = 0; i < obstacle_num; i++){
        obstacle_height = rand() % MAX_DEPTH + 1;
        obstacle_row = rand() % ROW;
        obstacle_col = rand() % COL;
        
        if(board[obstacle_row][obstacle_col][0].type == 'e' && (obstacle_col != 0 && obstacle_row != 0)){

            board[obstacle_row][obstacle_col] = (block_t *)realloc(board[obstacle_row][obstacle_col], sizeof(block_t) * obstacle_height+1);
            board[obstacle_row][obstacle_col][0].type = 'o';
            board[obstacle_row][obstacle_col][0].value = obstacle_height;

            for(j = 1; j < obstacle_height+1; j++){
            board[obstacle_row][obstacle_col][j].type = 'o';
            board[obstacle_row][obstacle_col][j].value = j;
            }
        }
        else{
            i--;
        }

    }

    // create bait block
    int bait_row, bait_col;
    for(int k=0;k<1;k++){
        bait_row = rand() % ROW;
        bait_col = rand() % COL;
        if(board[bait_row][bait_col][0].type == 'e' &&(bait_col != 0 && bait_row != 0)){
            board[bait_row][bait_col][0].type = 'b';
            board[bait_row][bait_col][0].value = 0;
        }
        else{
            k--;
        }
    }

   
    return board;
   
}   

void draw_board(block_t ***board,snake_t *snake,int snakesize){
    
    int i,j,k,t,flag=0;

    

    printf("\n");
    for(i=0;i<ROW;i++){
        for(t=0;t<ROW*4+1;t++){
        printf("-");
        }
        printf("\n");
        for(j=0;j<COL;j++){
            printf("|");
            flag=0;
            for(k=0;k<snakesize;k++){
                if(snake[k].row==i && snake[k].col == j && k!= 0){
                    printf(" X ");
                    flag=1;
                    k=snakesize+1;
                    
                }
                else if(snake[k].row==i && snake[k].col == j && k== 0){
                    printf(" O ");
                    flag=1;
                    k=snakesize+1;
                }
            }
            if(flag==0){

                if(board[i][j][0].type=='e'){
                    printf("%s","   "); 
                }

                else if(board[i][j][0].type=='b'){
                    printf(" . ");
                }

                else if(board[i][j][0].type=='o'){
                    printf(" %d ",board[i][j][0].value);
                }

            }
            
            
        }
        printf("|\n");
    }
    for(t=0;t<ROW*4+1;t++){
        printf("-");
        }
    printf("\n");
        
}

void play(block_t ***board){

    // init snake
    snake_t *snake;
    snake = (snake_t *)malloc(sizeof(snake_t));
    snake[0].row = 0;
    snake[0].col = 0;
    
    char move;
    printf(">");
    scanf(" %c",&move);

}

int check_status(const block_t ***board,const snake_t *snake,int snakesize,char move){
    
    switch(move){
        case 'w':

            if(snake[0].row == 0){
                return 1;
            }

            else if(board[snake[0].row-1][snake[0].col][0].type == 'o'){
                if(board[snake[0].row-1][snake[0].col][0].value > snakesize){
                    return 1;
                }
            } 
              
            for(int i=0;i<snakesize;i++){
                if(snake[i].row == snake[0].row-1 && snake[i].col == snake[0].col){
                    return 1;
                }
            }
            
            break;

        case 'a':

            if(snake[0].col == 0){
                return 1;
            }

            else if(board[snake[0].row][snake[0].col-1][0].type == 'o'){
                if(board[snake[0].row][snake[0].col-1][0].value > snakesize){
                    return 1;
                }
            }

            for(int i=0;i<snakesize;i++){
                if(snake[i].row == snake[0].row && snake[i].col == snake[0].col-1){
                    return 1;
                }
            }

            break;
        case 's':
            
            if(snake[0].row+1 == ROW){
                return 1;
            }

            else if(board[snake[0].row+1][snake[0].col][0].type == 'o'){
                if(board[snake[0].row+1][snake[0].col][0].value > snakesize){
                    return 1;
                }
            }
            for(int i=0;i<snakesize;i++){
                if(snake[i].row == snake[0].row+1 && snake[i].col == snake[0].col){
                    return 1;
                }
            }
            break;
        case 'd':

            if(snake[0].col+1 == COL){
                return 1;
            }

            else if(board[snake[0].row][snake[0].col+1][0].type == 'o'){
                if(board[snake[0].row][snake[0].col+1][0].value > snakesize){
                    return 1;
                }
            }
            for(int i=0;i<snakesize;i++){
                if(snake[i].row == snake[0].row && snake[i].col == snake[0].col+1){
                    return 1;
                }
            }
            break;

    }
    return 0;
}

