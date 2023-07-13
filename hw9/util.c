#include "util.h"

/*
 * init_board function
 * create board and return it 
 * board is 3 dimensional array
 * block has type and value
 * type is 'e' for empty block 'o' for obstacle block 'b' for bait block
 * value is 0 for empty block and bait block for obstacle block value is obstacle height
 * obstacle height is random number between 1 and 9 
 * bait block is random block
 */
block_t *** init_board(){
    srand(time(NULL));

    block_t ***board = (block_t ***)malloc(sizeof(block_t **) * ROW); // create board

    int i,j;
    // create board and fill with empty block 
    for(i = 0; i < ROW; i++){

        board[i] = (block_t **)malloc(sizeof(block_t *) * COL);

        for(j=0;j< COL ; j++){
        board[i][j]= (block_t*)malloc(sizeof(sizeof(block_t)));
        // default block is empty block
        board[i][j][0].type = 'e';
        board[i][j][0].value = 0;
        }

    }

    // create obstacle block
    int obstacle_row, obstacle_col,obstacle_height; 
    obstacle_height = rand() % MAX_DEPTH + 1; // create obstacle height between 1 and 9
    obstacle_col = 1 + rand() % (COL-1);  // create obstacle block except first row and first column
    obstacle_row = 1 + rand() % (ROW-1);  // create obstacle block except first row and first column
    
    board[obstacle_row][obstacle_col] = (block_t *)realloc(board[obstacle_row][obstacle_col], sizeof(block_t) * obstacle_height+1);
    board[obstacle_row][obstacle_col][0].type = 'o';
    board[obstacle_row][obstacle_col][0].value = obstacle_height;

    for(j = 1; j < obstacle_height+1; j++){
    board[obstacle_row][obstacle_col][j].type = 'o';
    board[obstacle_row][obstacle_col][j].value = j;
    }
    // end of create obstacle block

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
    // end of create bait block
    
    return board;

}

/*
 * draw_board function
 * draw board
 * if block is empty print " ", if block is bait print ".", if block is obstacle print obstacle height
 * if block is snake head print "O", if block is snake body print "X" 
*/
void draw_board(block_t ***board,snake_t *snake,int snakesize){
    
    int i,j,k,t,flag=0;

    // print top of board
    printf(" ");
    for(t=0;t<ROW;t++){
        printf("-");
        }
    printf("\n");

    // print board
    for(i=0;i<ROW;i++){
        printf("|");
        for(j=0;j<COL;j++){
            flag=0;
            for(k=0;k<snakesize;k++){
                if(snake[k].row==i && snake[k].col == j && k!= 0){ // if block is snake body print "X"
                    printf("X");
                    flag=1;
                    k=snakesize+1;
                    
                }
                else if(snake[k].row==i && snake[k].col == j && k== 0){ // if block is snake head print "O"
                    printf("O");
                    flag=1;
                    k=snakesize+1;
                }
            }
            if(flag==0){

                if(board[i][j][0].type=='e'){ // if block is empty print " "
                    printf("%s"," ");  
                }

                else if(board[i][j][0].type=='b'){ // if block is bait print "."
                    printf(".");
                }

                else if(board[i][j][0].type=='o'){ // if block is obstacle print obstacle height
                    printf("%d",board[i][j][0].value);
                }
            }  
        }
        printf("|\n");
    }
    // print bottom of board
    printf(" ");
    for(t=0;t<ROW;t++){
        printf("-");
        }
    printf("\n");
        
}

/*
 * play function
 * play game
 * get board ,create snake and init snake to top left corner 
 * play game until game over
*/
void play(block_t ***board){

    // init snake
    snake_t *snake; // snake is array of snake block
    int score = 1;
    int snakesize = 1;
    int old_pos ;
    int obsctacle_num = 1;
    snake = (snake_t *)malloc(sizeof(snake_t)); // create snake
    
    snake[0].row = 0; snake[0].col = 0; // init snake to top left corner

    draw_board(board,snake,snakesize); // draw board
    do{
        old_pos = move(snake); //move  and get old position of snake head
        if(check_status(board,snake,snakesize) == 1){ // check game status
            printf("Game Over\n");
            exit(0);
        }
        else{
            update(board,&snake,&snakesize,old_pos,&score,&obsctacle_num); // update board
            draw_board(board,snake,snakesize); // draw board

        }  
    }while(1);

    free(snake); // free snake

    


}

/***
 * check_status function
 * check game status
 * if snake hit itself or snake hit wall or obstacle that its height is higher than snake length return 1
 * else return 0
 */
int check_status(block_t ***board,const snake_t *snake,int snakesize){

    // find if snake hit itself , condition is head of snake has same row and col with other snake block
    for(int i=0;i<snakesize;i++){
        for(int j=i+1;j<snakesize;j++){
            if(snake[i].row == snake[j].row && snake[i].col == snake[j].col ){
                    printf("Game Over due to snake crashed itself\n");
                 return 1;
            }
        }
    }
    
    // find if snake hit wall
    if(snake[0].row < 0 || snake[0].row > ROW-1 || snake[0].col < 0 || snake[0].col > COL-1){
        printf("Game Over due to snake hit wall\n");
        return 1;
    }
    // find if snake hit obstacle and obstacle height is bigger than snake size
    if(board[snake[0].row][snake[0].col][0].type == 'o'){
        if(board[snake[0].row][snake[0].col][0].value > snakesize){
            printf("Game Over due to snake hit obstacle\n");
            return 1;
        }
    }    

    return 0;
}


/**
 * move function
 * get move from user
 * if move is valid head of snake is moved and return old position of snake head
 * else get move again
*/
int move(snake_t *snake){

        char mov;
        int old_pos = snake[0].row * COL + snake[0].col; // old position of snake head
        printf(">");
        scanf(" %c",&mov);
        if(mov != 'w' && mov != 'a' && mov != 's' && mov != 'd'){
            printf("Invalid move enter again!! \n"); // if move is invalid get move again
            move(snake);
        }

        // move snake head
        switch(mov){
            case 'w':
                snake[0].row--;
                break;
            case 'a':
                snake[0].col--;
                break;
            case 's':
                snake[0].row++;
                break;
            case 'd':
                snake[0].col++;
                break;
        } 
        return old_pos;
   
}


/**
 * update function
 * update board
 * if snake hit bait snake size increase by 1 
 * if snake hit obstacle snake , obstacle will be removed and create new obstacle with random height
 * if snake hit empty block snake move
*/
int update(block_t ***board,snake_t **snake,int *snakesize,int old_pos,int *score ,int *obstacle_num){
    
    snake_t *temp_snake = (snake_t *)malloc(sizeof(snake_t) * (*snakesize)); // create temp snake

    int i,j,k,flag; // i,j,k for loop , flag for check if snake hit something

    temp_snake[0].row = (*snake)[0].row; // temp snake head is new position of snake head
    temp_snake[0].col = (*snake)[0].col; // temp snake head is new position of snake head

    // if snake hit bait
    if(board[(*snake)[0].row][(*snake)[0].col][0].type == 'b'){
        (*snakesize)++; // snake size increase by 1
        temp_snake = (snake_t *)realloc(temp_snake,sizeof(snake_t) * (*snakesize)); // realloc temp snake
        board[(*snake)[0].row][(*snake)[0].col][0].type = 'e'; // change type of block to empty
        board[(*snake)[0].row][(*snake)[0].col][0].value = 0; // change value of block to 0

        // create new bait
        int bait_row,bait_col;
        do{
            bait_row = rand() % ROW;
            bait_col = rand() % COL;
        }while(board[bait_row][bait_col][0].type != 'e');

        board[bait_row][bait_col][0].type = 'b';
        board[bait_row][bait_col][0].value = 0;
        // end of create new bait
    
        
    }
    // if snake hit obstacle, remove obstacle and create new obstacle with random height
    else if(board[(*snake)[0].row][(*snake)[0].col][0].type  == 'o'){
            board[(*snake)[0].row][(*snake)[0].col][0].type = 'e';  
            board[(*snake)[0].row][(*snake)[0].col][0].value = 0;
            (*obstacle_num)--;
            }
    
    // create new obstacle every 5 score and increase obstacle value does exist
    if((*score) % 5 == 0 && *score != 0){
        for(i=0;i<ROW;i++){
            for(j=0;j<COL;j++){
                if(board[i][j][0].type == 'o'){
                   if(board[i][j][0].value < 9){
                        board[i][j][0].value++;
                   }
                }
            }
        }
        if(*obstacle_num < 3 ){
            int obstacle_row,obstacle_col;
            do{
                flag = 0;
                obstacle_row = rand() % ROW;
                obstacle_col = rand() % COL;
                for(i=0;i<(*snakesize);i++){
                    if(obstacle_row == (*snake)[i].row && obstacle_col == (*snake)[i].col){
                        flag = 1;
                        break;
                    }
                }
            }while(board[obstacle_row][obstacle_col][0].type != 'e' && flag !=1);

            board[obstacle_row][obstacle_col][0].type = 'o';
            board[obstacle_row][obstacle_col][0].value = rand() % 9 + 1;
            (*obstacle_num)++;
        }

       
    }
    // end of create new obstacle

    //set temp snake to actual snake position except head of snake 
    temp_snake[1].row = old_pos / COL;
    temp_snake[1].col = old_pos % COL;
    for(i=2;i<(*snakesize);i++){
            temp_snake[i].row = (*snake)[i-1].row;
            temp_snake[i].col = (*snake)[i-1].col;
    }
        
    *snake = (snake_t *)realloc(*snake,sizeof(snake_t) * (*snakesize));
    for(i=0;i<(*snakesize);i++){
        (*snake)[i].row = temp_snake[i].row;
        (*snake)[i].col = temp_snake[i].col;
    }
    // end of set temp snake to actual snake position except head of snake
    (*score)++; // increase score by 1
    free(temp_snake); // free temp snake
    return 0;
}