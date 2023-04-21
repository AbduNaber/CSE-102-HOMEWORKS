#include <stdio.h>
#include <math.h>

#define MAX_CHAR_LENGHT 255 // MAX FILE NAME LENGHT IN LINUX
#define TICTACTOE_SIZE 3    // TIK TAC TOE GAME BOARD SIZE

/*Function Declaration. For more info find out that function */
void print_board(char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE]);
void create_board(char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE]);
int update_board(int x,int y,int player, char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE]);



typedef enum {
    RED , 
    GREEN, 
    BLUE,
    YELLOW,
    ORANGE,
} Color;

Color mixer(Color color1, Color color2,float arr[6][3]);
Color colorMixer(Color color1, Color color2, float arr[6][3], Color (*func)(Color, Color, float (*)[3]));
void print_color(Color color,float arr[6][3]);
/*End  of Declaration*/

//reads  a text  file  and  counts  the  occurrences  of  each  letter  in  the  English alphabet (case-insensitive)
int part1(char filename[]){

    FILE *fp= fopen(filename,"r");// open file in read mode

    if(fp == NULL){
      printf("Error: Could not open file\n\n");
      return 1;
    } 

    int alphabet[26] = {0};// Array stores how many repeated char does it have. a is alphabet [0] so z is alphabet[25]

    char c;
    int locationLower= 'a';  // set at the begining of the alphabet 'a' 
    int locationUpper = 'A' ;  // set at the begining of the alphabet 'A' 

    /* increase alphabet array corresponding to char.(case-insensitive) */
    while((c=fgetc(fp))!=EOF){
        if(c>='a' && c<='z'){
            alphabet[c-locationLower]++; 
        }
        else if(c>='A' && c<='Z'){
            alphabet[c-locationUpper]++;
        }
    }

    /* display letter frequency*/
    printf("Letter Frequency:\n");
    for(int i=0;i<26;i++){
        printf("%c: %d\n",i+'A',alphabet[i]);
    }
    printf("\n");
    fclose(fp);//close file
}

/*COLOR SECTION PART*/
int part2(){
    
    /*Color vector declaration, Each color has own point.*/
    float color_vector[6][3] = { 
        {1.0,0.0,0.0}, // RED
        {0.0,1.0,0.0}, // GREEN
        {0.0,0.0,1.0}, // BLUE
        {0.5,0.5,0.0}, // YELLOW
        {0.5,0.4,0.2}, // ORANGE
        {0.0,0.0,0.0}, // NEW COLOR (Choosen from user it occurs mixer function)
    } ;
    

    char firstColor;
    char secondColor;
    Color color1;
    Color color2;
    
    /*COLOR SELECTION*/
    int flag=0;
    do{
        printf("Enter Color 1 (r,g,b,y,o): ");
        scanf(" %c",&firstColor);
        switch(firstColor){
            case 'r': color1 = RED; flag = 1; break;
            case 'g': color1 = GREEN; flag = 1; break;
            case 'b': color1 = BLUE; flag = 1; break;
            case 'y': color1 = YELLOW; flag = 1;  break;
            case 'o': color1 = ORANGE; flag = 1;  break;
            default : 
                printf("You entered undefined color\n");
                 
                break;
        }

    }while(!flag);

    flag=0;
    do{
        printf("Enter Color 2 (r,g,b,y,o): ");
        scanf(" %c",&secondColor);     
        switch(secondColor){
            case 'r': color2 = RED; flag =1; break;
            case 'g': color2 = GREEN; flag =1; break;
            case 'b': color2 = BLUE; flag =1; break;
            case 'y': color2 = YELLOW; flag =1; break;
            case 'o': color2 = ORANGE; flag =1; break;
            default :
                printf("You entered undefined color\n");
                  
             break;
        }
    }while(!flag);
    /*END OF SELECTION*/

    Color new_color = colorMixer(color1,color2,color_vector,&mixer);// mix the color. see colorMixer function

    /*display the mixed color*/
    printf("Mixed Color: ");
    switch(new_color){
        case RED: printf("RED "); print_color(new_color,color_vector); break;  
        case GREEN: printf("GREEN "); print_color(new_color,color_vector); break; 
        case BLUE: printf("BLUE "); print_color(new_color,color_vector); break; 
        case YELLOW: printf("YELLOW"); print_color(new_color,color_vector); break; 
        case ORANGE: printf("ORANGE"); print_color(new_color,color_vector); break;            
    } 
    /*end  of display*/  
}

/*
 *transition function to mixer
 *it takes Color,float array and pointer function as argument
 */
Color colorMixer(Color color1, Color color2, float arr[6][3], Color (*func)(Color, Color, float (*)[3] )){
    Color new_color = mixer(color1,color2,arr);
    return new_color;

}

/*                              mixer 
  *When the colors to be mixed has the followinglength-3 vectors [x1,x2,x3] and [y1,y2,y3], 
  *the mixed color is [(x1+y1)/2, (x2+y2)/2, (x3+yr)/2] 
  *the corresponding enumerated color is the closest to this one using Euclidean distance  
*/
Color mixer(Color color1, Color color2,float arr[6][3]){

    float distances[5]= {0.0,0.0,0.0,0.0,0.0}; // distances to each color (RED to ORANGE)
    Color final_color;

    /*calculation of new color*/
    for(int i=0;i<3;i++){
        arr[5][i]= (arr[color1][i]+arr[color2][i])/2;
    }

    /*calculation of distances to each color */
    for(Color i=RED;i<= ORANGE;i++){
        distances[i]= sqrt(pow(arr[5][0] - arr[i][0], 2) + pow(arr[5][1] - arr[i][1], 2) + pow(arr[5][2]-  arr[i][2],2));

    }

    float min_distance = distances[0];// set to distance to zero for determining min distance
    
    // determine Which color is closest to
    for(Color i=RED;i<= ORANGE;i++){

        if(min_distance > distances[i]){
            min_distance=distances[i];
            final_color=i;
        }
        
    }
    return final_color;

}
/* print the mixed color vector*/
void print_color(Color color,float arr[6][3]){
    printf("[%.2f, %.2f, %.2f]\n\n",arr[5][0],arr[5][1],arr[5][2]);
}


// CLASSIC TIC TAC TOE GAME
int part3(){

    char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE] ;
    int x,y; // user chosen location parameter 
    int status=0;// check win or resume game if it is 88 ('X') X is winner or if it is 79 ('O') O is winner
    int movec=0; // caunt movement of game, if it reachs 9, it stops the game 

    create_board(tictactoe);// creates empty board

    /*PLAYGROUND*/
    while( status != 'X'&& status != 'O'&& movec!=9 ){

            printf("player 1 (X), Enter your  move (row,col): ");
            scanf("%d %d",&x,&y);
            status = update_board(x,y,1,tictactoe);
            print_board(tictactoe);
            movec++;

            if(status != 'X' && movec!=9  ){

                printf("player 2 (O), Enter your  move (row,col): ");
                scanf("%d %d",&x,&y);
                status = update_board(x,y,2,tictactoe);
                print_board(tictactoe);
                 movec++;
            }
          
            }
    /*END OF PLAYGROUND*/

    if(status=='X'){
        printf("Player 1 (X) wins!\n");
    }
    else if(status=='O'){
        printf("Player 2 (O) wins!\n");
    }
    else{
        printf("NO WINNER, NO LOSER\n");
    }
    printf("END OF GAME GOOD BYE\n");
}

// Updates board according to user chosen X and Y location
// Additional Checks potential winner and return winner
int update_board(int x,int y,int player, char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE]){

    int status =0;
    int flag=0;

    //set the movement to board. If it is full, warn user
    while(!flag){

        if( tictactoe[x][y] == '_'){

            if(player ==1){
                tictactoe[x][y] =  'X';
            }

            else if (player ==2){
                tictactoe[x][y] =  'O';
            }
            flag =1;
        }
        else {
            printf("ENTER VALID MOVE: ");
            scanf("%d %d",&x,&y);
        }
    }
    
    // check potential winner in row.
    if(tictactoe[x][0]==tictactoe[x][1]&& tictactoe[x][1]== tictactoe[x][2]){
        status = tictactoe[x][y];
    }

    // check potential winner in column.
    else if (tictactoe[0][y]==tictactoe[1][y]&& tictactoe[1][y]== tictactoe[2][y] ){
        status = tictactoe[x][y];
    }

    // check potential winner in cross.
    else if((x==0 && y==0) || (x==1 && y==1) ||(x==2 && y==2) ){
        if((tictactoe[0][0]==tictactoe[1][1]) && (tictactoe[1][1]==tictactoe[2][2])){
            status = tictactoe[x][y];
        }
    } 

     return status;

    }

// CREATE BOARD
void create_board(char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE]){
    for (int i = 0; i < 3; i++){
         for (int j = 0; j < 3; j++){
            tictactoe[i][j] = '_';
         }
    }
}

// PRINT BOARD
void print_board(char tictactoe[TICTACTOE_SIZE][TICTACTOE_SIZE]){

     for (int i = 0; i < 3; i++){
         for (int j = 0; j < 3; j++){
            printf("%c ",tictactoe[i][j]);
         }
         printf("\n");
    }
}


int main(){

    char filename[MAX_CHAR_LENGHT] ; // store file name
    //prompts user to file name and send to part1 function
    printf("Enter the file name: "); 
    scanf("%s",filename);
    part1(filename);

    part2(); // COLOR MIXER
    part3();  // TICTACTOE GAME

    return 0;

}



