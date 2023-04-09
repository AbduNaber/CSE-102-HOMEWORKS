#include <stdio.h>
#include <stdlib.h>
#include <time.h>


<<<<<<< HEAD
=======
int readmenu(){

   FILE *fp;
   fp = fopen("menu.txt","r");

   char c;
   int counter;
   int no=2;
   printf("Yemek Listesi:\n");
   printf("1.");
   while((c =fgetc(fp)) != EOF){
        if(counter%2==0){
            printf("%c",c);
        }
        if(c==' '){
            counter++;
        }
        else if(c == '\n'){
            printf("\n%d.",no);
            no++;
            counter++;
        }
   }
}
int servising(){
    int product;
    int serving;
    int s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
    float price;
    FILE *fp = fopen("menu.txt","r");
    while(price != EOF){
        fscanf(fp,"%d",s1);
    }
    while(product !=0 || serving !=0){
        printf("Please choose a product (1-10): ");
        scanf("%d",product);
        printf("How many servings do you want? ");
        scanf("%d",serving);
        switch (product){
        case 1:
            s1= serving;
            break;
        case 2:
            s2= serving;
            break;
        case 3:
            s3= serving;
            break;
        case 4:
            s4= serving;
            break;
        case 5:
            s5= serving;
            break;
        case 6:
            s6= serving;
            break;
        case 7:
            s7= serving;
            break;
        case 8:
            s8= serving;
            break;
        case 9:
            s9= serving;
            break;
        case 10:
            s10= serving;
            break;
        default:
            break;
        }
    }
}
int recipt(){

}

int main(){
        readmenu();
        
        
}
>>>>>>> eadbb19da284bd3d4d34af1374a4a2717bee5242
