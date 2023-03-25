#include <stdio.h>



int part1(){
    /*this function uses to find GDC.  for more info look at https://en.wikipedia.org/wiki/Euclidean_algorithm*/

    int a; 
    int temp;
    int a; 
    int b;

    printf("enter first number: ");  /* gets first number from user */
    scanf("%d",&a);

    printf("enter second number: "); /* gets second number from user */
    scanf("%d",&b);

    /*algorithm of GDC . for more info go to https://en.wikipedia.org/wiki/Euclidean_algorithm and look at Implementations topic*/
    while(b!=0){ 
        temp = b;
        b = a%b;
        a = temp;
   }
    /*end of algorithm*/

    /*if user enters negative number, algorithm calculate negative number but GCD can not be negative. This part reverse nagative number to positive */
   if (a<0){
     return a*(-1);
   }
   else{
     return a;
   }
}

/* end of finding GCD function*/



void part2(){

    int a;
    int b;
    int sum;

    printf("first number : ");
    scanf("%d",&a);

    printf("second number: ");
    scanf("%d",&b);
    
    sum = a+b;

    //printf("Result:\n%12d\n%12d\n     +\n     -------\n%12d\n",a,b,sum);
    printf("Result:\n");
    printf("%12d\n",a);
    printf("%12d\n",b);
    printf("%6s\n","+");
    printf("%12s\n","-------");
    printf("%12d\n",sum);
}


void part3(){
    int a;
    int b;
    int product;

    printf("first number : ");
    scanf("%d",&a);

    printf("second number: ");
    scanf("%d",&b);

    product = a*b;

    printf("Result:\n");
    printf("%13d\n",a);
    printf("%13d\n",b);
    printf("%4s\n","*");
    printf("%13s\n","----------");

    int temp =b;
    int mod=10;
    int gap=13;

    while(temp!=0){
        printf("%*d\n",gap,a*(temp%mod));
        temp = temp - (temp%mod);
        temp = temp/10;
        gap = gap-1;
    }

    printf("%4s\n","+");
    printf("%13s\n","----------");
    printf("%13d\n",product);


}

int part4(){
    int a;
    printf("enter a number : ");
    scanf("%d",&a);

    if(1<a && a<10){
        if(a>5){
            printf("The integer you entered is greater than 5");
            return 0;
        }

        else if(a<=5){
            printf("The integer you entered is less than or equal to 5");
            return 0;
        }

    }

    else {
        printf("Invalid input");
        return 0;
    }
}


int main(){
 printf("GCD is = %d\n\n",part1());
 part2();
 part3();
 part4();



 return 0;
}