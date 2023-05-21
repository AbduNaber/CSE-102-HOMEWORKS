#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3

typedef struct {

    int board[ROW][COL];
    int number;
    char direction;
    int score;
    int best_score;
    
} puzzle8_t;

void create_board(puzzle8_t *puzzle);
int play(puzzle8_t *puzzle);
void print_board(puzzle8_t *puzzle);
int update_board(puzzle8_t *puzzle,int number,char move);
int check_board(puzzle8_t *puzzle);
int update_zero(puzzle8_t *puzzle,char move,int *location);
int isSolvable(puzzle8_t *puzzle);
int main(){
    
    puzzle8_t puzzle;
    create_board(&puzzle);
    print_board(&puzzle);
    /*
    int option;
    do{
         
         printf("Welcome to 8 puzzle game!\n"
           "Please select an option:\n"
            "1. Play game as a user\n"
            "2. Finish the game with PC\n"
            "3. Show the best score\n"
            "4. Exit\n"
            "> ");
        scanf("%d",&option);
        switch(option){
            case 1:
                play(&puzzle);
                break;
            case 2:
                printf("You selected option 2\n");
                break;
            case 3:
                printf("You selected option 3\n");
                break;
            case 4:
                printf("You selected option 4\n");
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
    } while(option != 4);
    */
   auto_play(&puzzle);
    return 0;

   
   
    

   }
    
void create_board(puzzle8_t *puzzle){
    srand(time(NULL));
    int numbers[9]= {0,1,2,3,4,5,6,7,8};
    int i,j;
    int random;
    
    do
    {for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            random = rand() % (ROW*COL);
            if(numbers[random] != -1){
                puzzle->board[i][j] = random;
                numbers[random] = -1;
            }
            else{
                j--;
            }
            
        }
    }
    }while(!isSolvable);


    

    
}

int play(puzzle8_t *puzzle){



   int flag=-1;
   while(flag != 0){
 
    printf("\n");
    printf("Enter a number and a move: ");
    scanf("%d-%c",&puzzle->number,&puzzle->direction);
    update_board(puzzle,puzzle->number,puzzle->direction);
    printtofile(puzzle);
    print_board(puzzle);
    flag = check_board(puzzle);
   }



}

void print_board(puzzle8_t *puzzle){

    int i,j;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(puzzle->board[i][j] != 0){
                printf("%d ",puzzle->board[i][j]);
            }
            else{
                printf("_ ");
            }
        }
        printf("\n");
    }
}

int update_board(puzzle8_t *puzzle,int number,char move){

    int i,j;

    if(number < 1 || number > 8){
        printf("Invalid number!\n");
        return -1;
    }

    if(move != 'U' && move != 'D' && move != 'L' && move != 'R'){
        printf("Invalid move!\n");
        return -1;
    }

    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(puzzle->board[i][j] == number){
                switch(move){
                    case 'U':
                        if(puzzle->board[i-1][j]== 0){
                            puzzle->board[i-1][j] = number;
                            puzzle->board[i][j] = 0;
                            break;
                        }
                        else{
                            printf("Invalid move!\n");
                            break;
                        }
                    case 'D':
                        if(puzzle->board[i+1][j]== 0){
                            puzzle->board[i+1][j] = number;
                            puzzle->board[i][j] = 0;
                            break;
                        }
                        else{
                            printf("Invalid move!\n");
                            break;
                        }
                    case 'L':
                        if(puzzle->board[i][j-1]== 0){
                            puzzle->board[i][j-1] = number;
                            puzzle->board[i][j] = 0;
                            break;
                        }
                        else{
                            printf("Invalid move!\n");
                            break;
                        }
                    case 'R':
                        if(puzzle->board[i][j+1]== 0){
                            puzzle->board[i][j+1] = number;
                            puzzle->board[i][j] = 0;
                            break;
                        }
                        else{
                            printf("Invalid move!1\n");
                            break;
                        }                 
                }
                j = COL+1;
                i = ROW+1;
            }

        }
    }

    return 0;
}

int check_board(puzzle8_t *puzzle){

    int i,j;
    int count = 1;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(puzzle->board[i][j] != count){
                return -1;
            }
            count++;
        }
    }
    return 0;
}

int printtofile(puzzle8_t *puzzle){
    FILE *fp;
    fp = fopen("board_history.txt","a+");
    if(fp == NULL){
        printf("Error opening board history file!\n");
        return -1;
    } 
    // print table to file add to --------------------
    int i,j;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(puzzle->board[i][j] != 0){
                fprintf(fp,"%d ",puzzle->board[i][j]);
            }
            else{
                fprintf(fp,"_ ");
            }
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    fclose(fp);
    
    
}

int countInversions(puzzle8_t *puzzle)
{
    int inv = 0;
    int i, j;
    int size = ROW; // Size of a 3x3 puzzle
    int number;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            number = puzzle->board[i][j];
            if (number == 0) // Skip the blank tile
                continue;
            
            for (int k = i; k < size; k++)
            {
                for (int l = (k == i) ? j + 1 : 0; l < size; l++)
                {
                    int compare = puzzle->board[k][l];
                    if (compare != 0 && number > compare)
                        inv++;
                }
            }
        }
    }
    return inv;
}

int isSolvable(puzzle8_t *puzzle){
    int inversions = countInversions(puzzle);
    int size = ROW; // Size of a 3x3 puzzle
    int blankRow = 0;

    // Find the row containing the blank tile
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (puzzle->board[i][j] == 0)
            {
                blankRow = size - i;
                break;
            }
        }
    }

    if (size % 2 != 0 && inversions % 2 == 0)
        return 1;

    else if (size % 2 == 0 && ((inversions + blankRow) % 2) != 0)
        return 1;
    else
        return 0;
}

int auto_play(puzzle8_t *puzzle){
    char moves[4]= {'U','D','L','R'};
    FILE *fp;
    fp = fopen("board_history.txt","a+");
    if(fp == NULL){
        printf("Error opening board history file!\n");
        return -1;
    }
    fprintf(fp,"***********NEW GAME***********\n");

    printf("AUTO PLAY STARTED\n");
  
    int location_of_zero;
    int i,j;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(puzzle->board[i][j] == 0){
                location_of_zero = i*3+j;
                i = ROW+1;
                j = COL+1;
            }
        }
    }
    int random=0;

    puzzle->direction = 'T';
    puzzle->score=0;
    auto_finish(fp,puzzle,location_of_zero,random,moves);
   fclose(fp);
    return 0;
}

auto_finish(FILE *fp,puzzle8_t *puzzle,int location_of_zero,int random,char moves[4]){

    random = rand() % 4;
    
    if(puzzle->direction == moves[random]){
        auto_finish(fp,puzzle,location_of_zero,random,moves);
    }
    
    else{
        puzzle->direction = moves[random];
    }
    printf("random is %d\n",random);
    if(!update_zero(puzzle,puzzle->direction,&location_of_zero)){
        printf("computer move is %c total moves %d\n",puzzle->direction,puzzle->score);
        printtofile(puzzle);
    }
    
 

    if(check_board(puzzle) == 0){
        printf("GAME OVER\n");
        printf("computer move is %c total moves %d\n",puzzle->direction,puzzle->score);
        return 0;
    }
    else{
        auto_finish(fp,puzzle,location_of_zero,random,moves);
    }
}

int update_zero(puzzle8_t *puzzle,char move,int *location){

    int i = *location/3;
    int j = *location%3;
    switch(move){
        case 'U':
            if(i-1 >= 0){
                puzzle->board[i][j] = puzzle->board[i-1][j];
                puzzle->board[i-1][j] = 0;
                *location = *location - 3;
                puzzle->score++;
                return 0;
            }
            else{
                return 1;
            }
        case 'D':
            if(i+1 < 3){
                puzzle->board[i][j] = puzzle->board[i+1][j];
                puzzle->board[i+1][j] = 0;
                puzzle->score++;
                *location = *location + 3;
                return 0;
            }
            else{
                return 1;
            }
        case 'L':
            if(j-1 >= 0){
                puzzle->board[i][j] = puzzle->board[i][j-1];
                puzzle->board[i][j-1] = 0;
                puzzle->score++;
                *location = *location - 1;
                return 0;
            }
            else{
                return 1;
            }
        case 'R':
            if(j+1 < 3){
                puzzle->board[i][j] = puzzle->board[i][j+1];
                puzzle->board[i][j+1] = 0;
                puzzle->score++;
                *location = *location + 1;
                return 0;
            }
            else{
                return 1;
            }
    }
}
    
   


