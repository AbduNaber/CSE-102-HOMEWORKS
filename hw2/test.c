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

    int m=9;
    int n=5;
    int int_num;
    double num = 1.020229;
    double temp_result1;
    int counter=0;
    int temp_result2;
    int digit_int = digit_counter(num);
    int e=0;
    
    for(int i=0;i<m-digit_int;i++){
        num = num*10;
        e--;
    }
    temp_result2 = num;

    if(temp_result2%10==9){
        temp_result2=temp_result2+1;
    }

    while(temp_result2%10==0){
        temp_result2 = temp_result2/10;
        e++;
    }

    temp_result1 = temp_result2/pow(10,n);
    e = e+n;
    int part_int = (int)temp_result1;
    double part_float = temp_result1 -(int)temp_result1;


    printf("%0*d%.*lfe%d",m-n-1,part_int,n,part_float,e);
}




void yedek2(){
    int m;
    int n;
    double num = 123.120023;
    long int temp_result;
    int counter=0;
    int digit=0;

    while (num / (long int)num != 1)  // loop runs until num/(int)num is 1
    {
        counter += 1;           // Adds 1 to count
        num *= 10;            // num is multipled by 10
    }
    printf("%da",counter);
    printf("%lf",num);
    
}

void yedek(){
    int m=8;
    int n = 4;

    double result= 12123.11;
    int result_int;
    double result_float;
    int digit_of_int ;
    int e=0;

    result_int = (int)result;
    result_float = result - result_int;
    digit_of_int = digit_counter(result_int);
    printf("aa%daa",digit_counter(result_int));




    while((m-n)>digit_of_int){
        result_int = result_int *10;
        result_int = result_int + (int)(result_float*10);
        result_float = (result_float*10)- (int)(result_float*10) ;
        digit_of_int++;
        e--;
    }
 
    while((m-n)<digit_of_int){ 
        result_float = (result_float/10)+ ((result_int%10)/10.0);
        result_int = (result_int - (result_int%10))/10;
        digit_of_int--;
        e++;
    }

    double sum = result_int + result_float;
    printf("%.*lfe%d",n,sum,e);
    
}