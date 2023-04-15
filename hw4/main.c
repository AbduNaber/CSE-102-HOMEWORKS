#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COSTUMER_NO "210104004072" // costumer no 
#define VAT 0.18 // VAT rate 
#define SDISCOUNT 0.125 // student discount is applied if costumer is student.
#define ADDISCOUNT 0.10 // additional discount is applied if price is more than 150.

/*Functions declaretion. For more info look at above that function*/
int readmenu();
int receipt_create();
int servising();
float receipt(int product,int serving,int wordc);
void bottom_reciept(float price_sum,char student);
int print_receipt();
int part1();
int part2();
/*End of function declaretion*/

int main(){

    part1();
    printf("\n");
    part2();
    return 0;
      
}

/*Read menu from menu.txt and prints to user*/
int readmenu(){

   FILE *fpm = fopen("menu.txt","r");// opens menu.txt file in read mode
   char c; 
   int no=2; 
   int counter=0; // for counting space and new line    



   /* 
    *printing meal algoritm
    * prints menu from menu.txt
    * this algoritm works in this way;
    
      0meal1price
      2meal3pirce
      4meal5price

      In menu.txt all new lines and spaces are treated as numbered. If counter is divided by 2 , prints char until reach space. 
   */
   printf("Yemek Listesi:\n");
   printf("1.");
   while((c =fgetc(fpm)) != EOF){ 
        if(counter%2==0){
            printf("%c",c);
        }
        if(c==' '){
            counter++; 
        }
        else if(c == '\n'){
            printf("\n%d.",no); // prints meal order
            no++;
            counter++;
        }
   }
    /*end of prints menu algorithm*/


   printf("\n");
   fclose(fpm); // closes file
}

/*create new receipt file and prints top of receipt in this file*/
int receipt_create(){

    /*declare time DAY.MONTH.YEAR/HOUR:MIN format*/
    time_t t= time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s,sizeof(s),"%d.%m.%Y/%H:%M",tm);

    FILE *fp = fopen("receipt.txt","w+");// open new receipt.txt file

    /*prints top of receipt according to PDF file*/
 
    fprintf(fp,COSTUMER_NO);
    fprintf(fp,"%24s\n",s);
    fprintf(fp,"------------------------------------\n");
    fprintf(fp,"Product                  Price (TL)\n");
    fprintf(fp,"-----------------------------------\n\n");
    /*end of printing top of receipt*/

    fclose(fp);// close file
}

int servising(){

    
    int product; // to store product number
    int serving; // to store serving number
    float price_sum =0 ; // sum of all price 
    char student;          // student flag

    while(1){

        //prompts user to get product number and how much serving
        printf("Please choose a product (1-10): ");
        scanf("%d",&product);
        printf("How many servings do you want? ");
        scanf("%d",&serving);
        
        //The customer will be able to request food until he presses 0. This if statement checks
        if(serving ==0 || product ==0){
            break;
        }

        /*
            *this switch case statement calls receipt func 
            *Each Word in menu.txt has own case.
            *For more info look at receipt func.
        */
        switch (product){

        case 1: // Kebap
            price_sum += receipt(1,serving,5);
            break;

        case 2: // Lahmacun
            price_sum +=receipt(2,serving,8);
            break;
        case 3: // Pide 
            price_sum += receipt(3,serving,4);
            break;

        case 4: // Döner 
            price_sum += receipt(4,serving,5);
            break;

        case 5: // Hamburger
            price_sum += receipt(5,serving,9);
            break;

        case 6: //Künefe 
            price_sum += receipt(6,serving,6);
            break;

        case 7: // Sütlaç
            price_sum += receipt(7,serving,6);
            break;

        case 8: // Kola
            price_sum += receipt(8,serving,4);
            break;

        case 9: // Su
            price_sum += receipt(9,serving,2);
            break;
             
        case 10: //Icetea
            price_sum += receipt(10,serving,6);
            break;

        default:
            printf("you entered out of range number\n");
            break;
        }
        
        
    }

    // Student check part
    printf("Are you student? (Y/N): ");
    scanf(" %c",&student);


    // prints bottom of receipt to receipt file. For more info look at bottom_receipt function.
    bottom_reciept(price_sum,student);
    
}

/*
 * RECEIPT FUNCTION  
 * This function prints products and prices in accordance with the line structure.
 * as a argument it takes product location,serving number and character count
 * for printing meals, it uses my printing meal algorithm
 * returns final price of product 
 * 
 */
float receipt(int product,int serving,int wordc){

    char c; // to print meal
    int counter=0; // to determine meal location
    int flag;   // printing meal flag 
    float price;    // final price of product 


    FILE *fpm = fopen("menu.txt","r"); // opens menu text file in read mode
    FILE *fpr = fopen("receipt.txt","a"); // opens receipt text file in append mode


    fprintf(fpr,"%2d*",serving); // prints serving number of meals to receipt

    flag=1;
    while(flag){ // this while prevent getting all char from menu file, If meals location is reached and printed to receipt, it will stop


    /* matching meal and product algoritm
    
      0meal1price
      2meal3pirce
      4meal5price

      In menu.txt all new lines and spaces are treated as numbered. If counter is equal to transformation of  product number prints meal to receipt
   */
        c = fgetc(fpm);
        if(counter==(2*product-2)){
            
            fprintf(fpr,"%c",c);

            if(c ==' ' || c == '\n'){ 
                flag=0; // to prevent 
            }
        }

        if(c ==' ' || c == '\n'){
            counter++;
        }

        }
    /*end of algorithm*/
    
   
    fscanf(fpm,"%f",&price);  /*gets the next float number fromwhere the meal and product matching algorithm left off in the menu file*/
    fprintf(fpr,"%*.*f\n",27-wordc,2,price*serving); // prints price of meal 

    fclose(fpr);
    fclose(fpm);

    return (price*serving); // sum of price of product
    }
 


/*
 * PRINTING BOTTOM OF RECEIPT FUNCTION
 * it prints bottom part of receipt 
 * as a argument, it takes sum price of all meal and student status
 */
void bottom_reciept(float price_sum,char student){

    float last_price = price_sum; // sum price of all meal

    FILE *fpr = fopen("receipt.txt","a"); // opens receipt file in append mode

    fprintf(fpr,"\ntotal:%*.*f\n",25,2,price_sum); // total price line 

    if(student=='y'){ // student check , if costumer is student, discount STUDENT DISCOUNT RATE, to change discount rate go to defination
        
        fprintf(fpr,"Student discount:%*.*f\n",14,2,price_sum*SDISCOUNT*-1);
        last_price = last_price - (price_sum*SDISCOUNT) ;
    }
    if(price_sum>150){ // price  check , if price is higher than 150 TL, discount ADDITIONAL DISCOUNT RATE, to change discount rate go to defination
        
        fprintf(fpr,"Additional discount:%*.*f\n",11,2,price_sum*ADDISCOUNT*-1);
        last_price = last_price - (price_sum*ADDISCOUNT) ;
    }

    fprintf(fpr,"-----------------------------------\n");
    fprintf(fpr,"Price:%*.*f\n",25,2,last_price); // last price line 
    fprintf(fpr,"Price + VAT:%*.*f\n\n",19,2,last_price+(last_price*VAT)); // price+VAT tax line

    fclose(fpr);
}

/*
 * prints receipt from receipt file 
 */
int print_receipt(){
    FILE *fpr = fopen("receipt.txt","r");
    char c;
    while((c=fgetc(fpr))!=EOF){
        printf("%c",c);
    }
    fclose(fpr);
}

/*
 * MENU AND RECEIPT PROGRAM
 * FOR MORE INFO GO TO WHEREVER THIS FUNC IS
 */
int part1(){
    readmenu(); 
    receipt_create();
    servising();
    print_receipt();
}


/* 
 *  ROCK,PAPER and SCISSORS GAME 
 *  YOU AND COMPUTER ARE PLAYER.
 *  You picks one of them,  so does computer
 */
int part2(){

    int choice; // user's choice
    int comp_choice; // computer's choice
    int flag=0; // flag to exit the loop
    char exit_status; // user's input to play again or not
    srand(time(NULL)); // initialize random seed

    while(!flag){ // loop until flag is true

        printf("Please make a choice!\n");
        printf("1: Stone, 2: Paper, 3: Scissors\n");
        scanf("%d",&choice); // read user's choice

        comp_choice = (rand()%2)+1; // generate computer's choice randomly

        switch(choice){ // compare user's choice and computer's choice

            case 1: // user chose stone
                if(comp_choice==1){
                    printf("You chose Stone. I chose Stone. It's a tie!\n");
                }
                else if(comp_choice==2){
                    printf("You chose Stone. I chose Paper. You won!\n");
                }
                else if(comp_choice==3){
                    printf("You chose Stone. I chose Scissors. I won!\n");
                }
                break;

            case 2: // user chose paper
                if(comp_choice==1){
                    printf("You chose Paper. I chose Stone. I won!\n");
                }
                else if(comp_choice==2){
                    printf("You chose Paper. I chose Paper. It's a tie!\n");
                }
                else if(comp_choice==3){
                    printf("You chose Paper. I chose Scissors. You won!\n");
                }
                break;

            case 3: // user chose scissors
                if(comp_choice==0){
                    printf("You chose Scissors. I chose Stone. You won!\n");
                }
                else if(comp_choice==1){
                    printf("You chose Scissors. I chose Paper. I won!\n");
                }
                else if(comp_choice==2){
                    printf("You chose Scissors. I chose Scissors. It's a tie!\n");        
                }
                break;
            default:
                printf("JUST ENTER 1-2-3\n"); // invalid input
        }
        
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c",&exit_status); // read user's input to play again or not
        printf("\n");
        if(exit_status=='n' || exit_status =='N'){
            flag =1; // set flag to true to exit the loop
        }
    }
    printf("GOOD BYE!\n"); // end of the program

}



