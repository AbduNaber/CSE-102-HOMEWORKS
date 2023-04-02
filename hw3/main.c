#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

int status(int d,int c);
int draw_room(int size,int d,int c);
int gameplay();


int draw_room(int size,int d,int c){

    if(d!=c){
        int counter=0;

    for(int i=0; i<size*2+1; i++){
        printf("-");
    }
    printf("\n");
    for(int i=0;i<size;i++){
        
        for (int i = 0; i < size; i++){
            if(counter==d){
                printf("|D");
                counter++;
            }
            else if(counter==c){
                printf("|C");
                counter++;
            }
            else{
                printf("| ");
                counter++;
            }
        }
    printf("|\n");
    }


    for(int i=0; i<size*2+1; i++){
        printf("-");
    }
    printf("\n");
    }
    return 0;
}

int gameplay(){
    int movecount=0;
    int size;
    int check;

    printf("enter a size: ");
    scanf("%d",&size);

    while(size<5 || size>10){
        printf("you cannot specify a size smaller than 5 or greater than 10. Enter different size: ");
        scanf("%d",&size);
    }


    srand(time(NULL));
    int d = rand()%(size*size);
    int c = rand()%(size*size);
    draw_room(size,d,c);

    char move;
    char temp ;
    char ch;
    int flag;
    do{

        flag=1;
        while(flag){
            printf("enter where you want to move(w,a,s,d): ");
            scanf(" %c", &move);
            ch = getchar();
            if (ch != '\n') {
                printf("Error: Please enter only one character.\n");
                while ( ch!= '\n' ){
                    ch = getchar();
                }
            continue;
        } 
        flag =0;
        }
        
        
        

        switch (move){
            case UP:
                if(c<=size-1){
                    printf("THEEE WALL!! CHOOSE ANOTHER MOVEMENT\n"); 
                }
                else{
                    c=c-size;
                    draw_room(size,d,c);
                    movecount++; 
                }
                break;
            case LEFT:
                if(c%size==0){
                    printf("THEEE WALL!! CHOOSE ANOTHER MOVEMENT\n");
                }
                else{
                    c=c-1;
                    draw_room(size,d,c);
                    movecount++; 
                }
                break;
            case DOWN:
                if(size*(size-1)<=c && c<size*size && c!=0){
                    printf("TTHEEE WALL!! CHOOSE ANOTHER MOVEMENT\n");
                }
                else{
                    c=c+size;
                    draw_room(size,d,c);
                    movecount++; 
                }
                break;

            case RIGHT:
                if((c-size+1)%(size)==0 && c!=0){
                    printf("THEEE WALL!! CHOOSE ANOTHER MOVEMENT\n");
                }
                else{
                    c=c+1;
                    draw_room(size,d,c);
                    movecount++; 
                }
                break;

            default:
                printf("enter valid movement!!(w,a,s,d)\n");
                break;
            }
        
        }
        while(!status(d,c));

        printf("you moved %dth times and succeeded\n",movecount);
        }
        
          
int status(int d,int c){
    if(d==c){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    int choice;
    int status =1;

    while(status){
    printf("Welcome to the 2D puzzle game!\n");
    printf("1. New Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");

    scanf("%d",&choice);

    switch (choice){
    case 1:
        gameplay();
        break;
    case 2:
        printf("---------------------------------------------2D PUZZLE GAME HELP MENU-------------------------------------------------------------------------------------\n"
                "1)You control a character in a 2D room with walls and a door.\n"
                "2)You can move the character one space at a time using the keys 'a' for left, 'd' for right, 'w' for up, and 's' for down.\n"
                "3)Diagonal moves are not allowed.\n"
                "4)After each move, the game will prompt you for a new move until you reach the door.\n"
                "5)If you try to move through a wall, a warning message will be displayed.\n"
                "6)The current state of the room will be printed after each move, except when you reach the door.\n"
                "7)The game ends when you reach the door, and a message will be displayed with the number of moves you made.\n"
                "8)Remember, using any control or selection with [a, d, w, s characters other than those defined at the beginning of the code will result in a missgrading.\n"
                "----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                
                break;
    case 3:
        printf("Goodbye player1!\n");
        status =0;
        break;
    default:
        printf("You must enter valid choice! try again \n");
        break;
    }


    }
    return 0;
    
}
