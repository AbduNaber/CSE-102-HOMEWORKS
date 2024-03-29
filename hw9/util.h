#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ROW 10
#define COL 10
#define MAX_DEPTH 9

typedef struct{
    char type;
    int value;
} block_t;


typedef struct {
    int row;
    int col;
} snake_t;

block_t *** init_board();
void play(block_t ***block);
void draw_board(block_t ***board,snake_t *snake,int snakesize);
int check_status(block_t ***board,const snake_t *snake,int snakesize);
int move(snake_t *snake);
int update(block_t ***board,snake_t **snake,int *snakesize,int old_pos,int *score,int *obsctacle_num);

#endif /* _UTIL_H_ */