#include <stdio.h>
#include "util.h"

/* this function uses to calculate GDC. for more info look at link*/
int part1(){

    /*variables using for GCD*/
    int temp;
    int a;
    int b;

    printf("enter first number: "); /*gets first number from user*/
    scanf("%d",&a);

    printf("enter second number: "); /*gets second number from user*/
    scanf("%d",&b);

    /*algorithm of calculating GDC. For more info go to link and look at Implemantations topic*/
    while(b!=0){
        temp = b;
        b = a%b;
        a = temp;
   }
   /*end of algoritm*/

   /*If user enters negative number, algorithm calculates negative GCD, but GCD can not be negative. This part reverse negative number to positive*/ 
   if (a<0){
     return a*(-1);
   }
   else{
     return a;
   }
}
/* end of calculating GCD function*/

/* this function takes two numbers from the user and displays their sums as if the arithmetic is done on*/
void part2(){

    /*variables using for sum*/
    int a;
    int b;
    int sum;

    /*gets numbers from user*/
    printf("first number : ");
    scanf("%d",&a);

    printf("second number: ");
    scanf("%d",&b);
    /*end of getting*/

    sum = a+b; /* answer of sum*/

    /* displays on cmd as if it does on paper*/
    printf("Result:\n");
    printf("%12d\n",a);
    printf("%12d\n",b);
    printf("%6s\n","+");
    printf("%12s\n","-------");
    printf("%12d\n\n",sum);
    /*end of displaying*/
}
/* end of summing two number function*/
/* this function counts digit of given number*/
int digit_counter(int a){
    
    int counter = 0; /*to count digit*/
    
    /*increase digit counter until given number has no digit*/
    while(a !=0){
        counter++; /* increase digit counter */

        /*reduce one digit of given number*/
        a = a - (a%10);
        a = a/10;
    }

    return counter;
}

/*his function takes 2 number from user and does it using multiplication table as as if done manually on paper*/
void part3(){

    /*integer variables use for product  */
    int a;
    int b;
    int product; /*to store the product of a and b*/

    /*Prompt the user to enter the first integer.*/
    printf("first number : ");
    scanf("%d",&a);

    /*Prompt the user to enter the first integer.*/
    printf("second number: ");
    scanf("%d",&b);

    product = a*b; /*Calculate the product of the two integers.*/

    /*Prints the multiplication table.*/
    printf("Result:\n");
    printf("%13d\n",a);
    printf("%13d\n",b);
    printf("%4s\n","*");
    printf("%13s\n","----------");
    
    /* variables use for multiplication table's row*/
    int temp =b; 
    int mod=10;  
    int gap=13;

    /*if multiplication table has row more than one, prints end of multiplication table (rows are second part of multiplication table that you do sum in here )*/
    if(digit_counter(a) !=1 && digit_counter(b) !=1){

        /* this algorithm calculates one row of multiplication table and shifts left and does it again until finished */
        while(temp!=0){
        printf("%*d\n",gap,a*(temp%mod)); /*prints one row*/
        
        /*reduces one digit */
        temp = temp - (temp%mod);
        temp = temp/10;

        /*shifts left*/
        gap = gap-1;
    }
        printf("%4s\n","+");
        printf("%13s\n","----------");
        printf("%13d\n\n",product);
    }
    
    /* if one of number's digit is one ,just print product*/
    else{
        printf("%13d\n\n",product);
    }
}
/* end of printing multiplication table*/




/*this function prompts for integer in [1,10], outputs its relation to 5 and outputs "Invalid input" for values outside of range. */
int part4(){

    /*Declare an integer variable to store the user input*/ 
    int a;

    /*gets numbers from user*/
    printf("Enter a number: ");
    scanf("%d", &a);

    // Check if the user input is within the range of 1 to 10 (inclusive)
    if (1 <= a && a <= 10) {

        /*If the input is greater than 5, print a message indicating so*/ 
        if (a > 5) {
            printf("The integer you entered is greater than 5\n");
            return 0;
        }

        /*If the input is less than or equal to 5, print a message indicating so*/ 
        else if (a <= 5) {
            printf("The integer you entered is less than or equal to 5\n");
            return 0;
        }
    }

    /*If the input is not within the range of 1 to 10 (inclusive), print an error message*/ 
    else {
        printf("Invalid input\n");
        return 0;
    }
}
/* end of checking relation to 5 function*/
