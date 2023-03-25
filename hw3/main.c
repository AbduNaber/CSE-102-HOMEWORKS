#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int status(int d,int c);
int draw_room(int size,int d,int c);
int gameplay();


int draw_room(int size,int d,int c){

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
    return 0;
}

int gameplay(){

    int size;
    printf("enter a size: ");
    scanf("%d",&size);

    srand(time(NULL));
    int d = rand()%(size*size);
    int c = rand()%(size*size);
    draw_room(size,d,c);

    printf("deneme");
    char move;

    while(!status(d,c)){
        printf("enter when you want to move(w,a,s,d): ");
        scanf(" %c",&move);
        printf("aaa%daaa\n",c);
        switch (move){
    case 'w':
        if(c<=9){
           printf("THEEE WALLLLL!!!!\n"); 
        }
        else{
           c=c-size;
           draw_room(size,d,c); 
        }
        break;
    case 'a':
        if(c%size==0){
            printf("THEEE WALLLLL!!!!\n");
        }
        else{
            c=c-1;
            draw_room(size,d,c);
        }
        break;
    case 's':
        if(size*(size-1)<=c && c<size*size){
            printf("THEEE WALLLLL!!!!\n");
        }
        else{
            c=c+size;
            draw_room(size,d,c);
        }
        break;

    case 'd':
        if(c%(size-1)==0){
            printf("THEEE WALLLLL!!!!\n");
        }
        else{
            c=c+1;
            draw_room(size,d,c);
        }
        break;
    default:
        printf("enter valid movement!!\n");
        break;
    }
    }
    


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
    gameplay();
}