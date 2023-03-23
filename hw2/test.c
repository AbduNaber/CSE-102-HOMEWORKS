#include <stdio.h>
#include <time.h>
#include <math.h>
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
        
}

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
int main() {
    int m=8;
    int n = 2;

    double result= 123.4567;
    int result_int;
    double result_float;
    int digit_of_int ;
    int e=0;

    result_int = (int)result;
    result_float = result - result_int;
    digit_of_int = digit_counter(result_int);
    printf("aa%daa",digit_counter(result_int));

    while((m-n)>digit_of_int){
        e++;
        result_int = result_int *10;
        result_int = result_int + (int)(result_float*10);
        result_float = (result_float*10)- (int)(result_float*10) ;
        digit_of_int++;
    }
    double sum = result_int + result_float;
    printf("%.*lfe%d",sum,e);
    
        
    

}