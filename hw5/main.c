#include <stdio.h>

#define MAX_CHAR_LENGHT 255

int part1(char filename[]){

    FILE *fp= fopen(filename,"r");

    int alphabet[26] = {0};

    char c;
    int locationLower= 'a';  // set at the begining of the alphabet 'a' 
    int locationUpper = 'A' ;  // set at the begining of the alphabet 'A' 

    while((c=fgetc(fp))!=EOF){
        if(c>='a' && c<='z'){
            alphabet[c-locationLower]++;
        }
        else if(c>='A' && c<='Z'){
            alphabet[c-locationUpper]++;
        }
    }

    printf("Letter Frequency:\n");
    for(int i=0;i<26;i++){
        printf("%c: %d\n",i+'A',alphabet[i]);
    }
    fclose(fp);
}

int part3(){
    char tictactoe[3][3] ;
    int x,y;
    int flag=0;

    int player;
    create_board(tictactoe);
    while(!flag){

            printf("player 1 (X), Enter your  move (row,col): ");
            scanf("%d %d",&x,&y);
            flag = update_board(x,y,1,tictactoe);
            print_board(tictactoe);
        
        if (!flag){
            printf("player 2 (O), Enter your  move (row,col): ");
            scanf("%d %d",&x,&y);
            flag = update_board(x,y,2,tictactoe);
            print_board(tictactoe);
        }
    }

    if(flag==1){
        printf("Player 1 (X) wins!\n");
    }
    else if(flag==2){
        printf("Player 2 (O) wins!");
    }
    
    

}
int update_board(int x,int y,int player, char tictactoe[3][3]){
    int check_row=0;
    int check_col=0;

    if(player ==1){
        tictactoe[x][y] =  'X';
    }
    else if (player ==2){
        tictactoe[x][y] =  'O';
    }

    for(int c=0;c<3;c++){
        for(int r=0;r<3;r++){

            if(tictactoe[c][r]=='X'){
                check_row= check_row +'X';
            }

            else if(tictactoe[c][r]=='O'){
                check_row= check_row +'O';
            }

        }
        if(check_row/3=='O' || check_row/3=='X'){
            return check_row/3;
        }
        else{
            check_row =0;
        }

    }

    
}


void create_board(char tictactoe[3][3]){
    for (int i = 0; i < 3; i++){
         for (int j = 0; j < 3; j++){
            tictactoe[i][j] = '_';
         }
    }
}


void print_board(char tictactoe[3][3]){

     for (int i = 0; i < 3; i++){
         for (int j = 0; j < 3; j++){
            printf("%c",tictactoe[i][j]);
         }
         printf("\n");
    }


}

int main(){

    char filename[MAX_CHAR_LENGHT] ;
    printf("Enter the file name: ");
    scanf("%s",filename);
    part1(filename);



}