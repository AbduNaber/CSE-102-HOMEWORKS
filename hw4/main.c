#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COSTUMER_NO "210104004072"
#define VAT 0.18
#define SDISCOUNT 0.125
#define ADDISCOUNT 0.10

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
   fclose(fp);
}

int receipt_create(){
    time_t t= time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s,sizeof(s),"%d.%m.%Y/%H:%M",tm);

    FILE *fp = fopen("receipt.txt","w"); 
    fprintf(fp,COSTUMER_NO);
    fprintf(fp,"%24s\n",s);
    fprintf(fp,"------------------------------------\n");
    fprintf(fp,"Product                  Price (TL)\n");
    fprintf(fp,"-----------------------------------\n");

}

int servising(){
    int product;
    int serving;
    
    float price;
    FILE *fpm = fopen("menu.txt","r");
    FILE *fpr = fopen("receipt.txt","a"); 
    while(price != EOF){
        fscanf(fp,"%d",s1);
    }
    while(product !=0 || serving !=0){
        printf("Please choose a product (1-10): ");
        scanf("%d",product);
        printf("How many servings do you want? ");
        scanf("%d",serving);

    }
}

int recipt(){

}

int main(){
        receipt_create();
        
        
}