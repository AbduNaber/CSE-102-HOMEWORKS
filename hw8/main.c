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
    int last_play;
    int best_score;
    
} puzzle8_t;

void create_board(puzzle8_t *puzzle);
int play(puzzle8_t *puzzle);
void print_board(puzzle8_t *puzzle);
int update_board(puzzle8_t *puzzle,int number,char move);
int check_board(puzzle8_t *puzzle);

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

int isSolvable(puzzle8_t *puzzle){
    
    int lineer_table[9];
    int i,j,k;
    int c=0;
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            lineer_table[c]=puzzle->board[i][j];
            c++;
        }
    }
    int inv_count = 0;
    for(k=0;k<9;k++){
        for(i=k+1;i<9;i++){
            if(lineer_table[i] && lineer_table[k] && lineer_table[k] > lineer_table[i]){
                inv_count++;
            }
        }
    }
    if(inv_count % 2 == 0){
        return 1;
    }
    else{
        return 0;
    }
    
}

int auto_play(puzzle8_t *puzzle){

    FILE *fp;
    fp = fopen("board_history.txt","a+");
    if(fp == NULL){
        printf("Error opening board history file!\n");
        return -1;
    }   
    printf("Auto play mode is on!\n");
    puzzle->score = 0;
    
    int randomMove;
    while(check_board){
        auto_finish(puzzle,&randomMove);
    }
    printf("Game is over!\n");
    printf("Computer score is %d\n",puzzle->score);
}
 
void auto_finish(puzzle8_t *puzzle,int *randomMove){
    char move[4] = {'U','D','L','R'};
    *randomMove = rand() % 4;
    if((puzzle->last_play == 'U' && move[*randomMove] == 'D') || (puzzle->last_play == 'D' && move[*randomMove] == 'U') || (puzzle->last_play == 'L' && move[*randomMove] == 'R') || (puzzle->last_play == 'R' && move[*randomMove] == 'L')){
        auto_finish(puzzle,randomMove);
    }

    if(isLegal(puzzle,randomMove)){
        
        updateZero(puzzle,randomMove);
        printtofile(puzzle);
        print_board(puzzle);
    }
    else{
        auto_finish(puzzle,randomMove);
    }

}

int  isLegal(puzzle8_t *puzzle , int *randomMove){
    char move[4] = {'U','D','L','R'};
    int i,j;
    for(i = 0; i< ROW; i++ ){
        for(j=0 ; j< COL; j++){
        if(puzzle->board[i][j]==0){
            switch(move[*randomMove]){
                case 'U':
                    if(i==0) return 0;
                    else return 1;
                case 'D':
                    if(i==2) return 0;
                    else return 1;
                case 'L':
                    if(j==0) return 0;
                    else return 1;
                case 'R':
                    if(j==2) return 0;
                    else return 1;

            }
        }
        }
    }
}

/*

*/
void updateZero(puzzle8_t *puzzle , int *randomMove){
    char move[4] = {'U','D','L','R'};
    int i,j;
    for(i = 0; i< ROW; i++ ){
        for(j=0 ; j< COL; j++){
        if(puzzle->board[i][j]==0){

            switch(move[*randomMove]){
                case 'U':
                    puzzle->board[i][j] = puzzle->board[i-1][j];
                    puzzle->board[i-1][j] = 0;
                    break;
                case 'D':
                    puzzle->board[i][j]=puzzle->board[i+1][j];
                    puzzle->board[i+1][j]=0;
                    break;
                case 'L':
                    puzzle->board[i][j]=puzzle->board[i][j-1];
                    puzzle->board[i][j-1]=0;
                    break;
                case 'R':
                    puzzle->board[i][j]=puzzle->board[i][j+1];
                    puzzle->board[i][j+1]=0;
                    break;
            }
            i = ROW+1;
            j = COL+1;
        }
        }
    }
    //printf("computer move is %d-%c",puzzle->board[i][j],move[*randomMove]);
    puzzle->last_play = move[*randomMove];
    puzzle->score++;

}

   


