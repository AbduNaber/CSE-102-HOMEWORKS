#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* CONTROL KEYBIND */
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'


/*decleration of function. For more info look at function where is*/
int status(int d,int c);
int draw_room(int size,int d,int c);
int gameplay();

int main(){
    int choice; // menu choice
    int status =1; // for menu loop 

    while(status){

    /*THE GAME MENU*/
    printf("Welcome to the 2D puzzle game!\n");
    printf("1. New Game\n");
    printf("2. Help\n");
    printf("3. Exit\n");
    scanf("%d",&choice);

    // A switch statement to perform the appropriate action based on the user's choice
    switch (choice){
    case 1:
        gameplay();  // Calling the gameplay function to start a new game
        break;

    case 2:
         // Displaying the help menu
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
        // Quitting the game
        printf("Goodbye player1!\n");
        status =0;
        break;
    default:
        // Prompting the user to enter a valid choice
        printf("You must enter valid choice! try again \n");
        break;
    }
    }

    return 0;
    
}

/*this function draw table according to size. D is a door location and C is a player location*/
int draw_room(int size, int d, int c){

    // Check if the door and player positions are different
    if (d != c) {
        int counter = 0; // position counter . it holds which room is printed . 

        // Print top row of dashes
        for (int i = 0; i < size*2+1; i++) {
            printf("-");
        }
        printf("\n");

        // Print rows of pipes with door or player or empty space
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // If the counter equals the position of door d, print "D" and increment counter
                if (counter == d) {
                    printf("|D");
                    counter++;
                }
                // If the counter equals the position of player, print "C" and increment counter
                else if (counter == c) {
                    printf("|C");
                    counter++;
                }
                // If the counter doesn't equal either door and player position, print empty space and increment counter
                else {
                    printf("| ");
                    counter++;
                }
            }
        printf("|\n"); // End the row with a pipe symbol
        }

        // Print bottom row of dashes
        for (int i = 0; i < size*2+1; i++) {
            printf("-");
        }
        printf("\n");
    }
    return 0;
}

/* gameplay function */
int gameplay(){

    int movecount=0; // initialize move count to 0
    int size; // size of board 
    
    // prompt user to enter a valid size
    printf("enter a size: ");
    scanf("%d",&size);

    // check if size is within valid range (5-10), otherwise prompt user to enter a valid size
    while(size<5 || size>10){
    printf("you cannot specify a size smaller than 5 or greater than 10. Enter different size: ");
    scanf("%d",&size);
    }

    srand(time(NULL)); // seed random number generator with current time
    int d = rand()%(size*size); // generate random location for 'D'
    int c = rand()%(size*size); // generate random location for 'C'
    draw_room(size,d,c); // call the function to draw the room

    char move; // initialize variable to hold user's move input

    /* THESE PART CHECK USER'S INPUT IF HE ENTERS ONE CHAR*/
    char ch;
    int flag;

    do{
    flag=1; // set flag to true to begin loop
    while(flag){ // keep looping until valid input is entered

        //prompt user to enter move
        printf("enter where you want to move(w,a,s,d): "); 
        scanf(" %c", &move);

        ch = getchar(); // gets char from buffer 
        if (ch != '\n') { // check if user entered more than one character
            printf("Error: Please enter only one character.\n");
            while ( ch!= '\n' ){ // flush out the buffer
                ch = getchar();
            }
        continue; // if user enters chars more than one return prompt
    } 
    flag =0; // set flag to false to break loop
    }
    /*END OF CHECKING ONE CHAR*/

    
    // check the user's input and move the character accordingly
    switch (move){
        case UP:
            if(c<=size-1){
                printf("THEEE WALL!! CHOOSE ANOTHER MOVEMENT\n"); 
            }
            else{
                c=c-size; // change player location according to UP move
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
                draw_room(size,d,c); // change player location according to LEFT move
                movecount++; 
            }
            break;
        case DOWN:
            if(size*(size-1)<=c && c<size*size && c!=0){
                printf("TTHEEE WALL!! CHOOSE ANOTHER MOVEMENT\n");
            }
            else{
                c=c+size; // change player location according to DOWN move
                draw_room(size,d,c);
                movecount++; 
            }
            break;

        case RIGHT:
            if((c-size+1)%(size)==0 && c!=0){
                printf("THEEE WALL!! CHOOSE ANOTHER MOVEMENT\n");
            }
            else{
                c=c+1; // change player location according to RIGHT move
                draw_room(size,d,c);
                movecount++; 
            }
            break;

        default:
            printf("enter valid movement!!(w,a,s,d)\n");
            break;
        }
        
    }
    while(!status(d,c)); // keep looping until user reaches the destination

    // print message indicating number of moves and success
    printf("you moved %dth times and succeeded\n",movecount);
}

        
        
 /*to check position status*/         
int status(int door_position, int player_position) {
    // If the player's position is the same as the door's position,
    // the player has reached the door, so return 1 (true)
    if (door_position == player_position) {
        return 1;
    }
    // Otherwise, the player is still far from the door, so return 0 (false)
    else {
        return 0;
    }
}

