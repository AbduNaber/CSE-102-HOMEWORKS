#include <stdio.h>
#include <math.h>


// declare functions. FOR MORE INFO FIND THAT FUNCTION BELOW MAIN FUNCTION
void part1();
void part2();
void part3();
double calculation(char operator, double operand1, double operand2);
int digit_counter(int a);
void display(char format, int m, int n,double operand1, double operand2, double result,char operator);
float calculate_grade(float exam1 ,float exam2 ,float exam3,float assign1,float assign2);


int main(){
    part1(); // leap year problem
    part2(); // Enhanced Calculator
    part3(); // Grade Calculator
    return 0;
}

// function prints entered number is leap year or not , for more ditail look at  https://en.wikipedia.org/wiki/Leap_year#Algorithm
void part1(){

    int year; //declare variable year

    // Prompt the user to enter a year
    printf("***************************\n");
    printf("Please enter a year: ");
    scanf("%d",&year);

    // Check if the year is divisible by 400
    if (year%400==0){
        printf("%d is  a leap year\n",year);
    }

    // Check if the year is divisible by 4 but not divisible by 100
    else if (year%4==0 && year%100 != 0){
        printf("%d is  a leap year\n",year);
    }
    // if all condition don't stisfield, print not a leap year
    else {
        printf("%d is not a leap year\n",year);
    }
}
// end of leap year function

// The function calculates according to the operator and returns a result for use in display.
double calculation(char operator, double operand1, double operand2){

    double result =1; // holds result of the operation

    // Switch statement to perform the operation based on the operator
    switch (operator){

        //sum operation
        case '+':
            result= operand1+operand2;
            break;
        
        //subtraction operation
        case '-':
            result= operand1-operand2;
            break;

        //division  operation
        case '/':
            result = operand1 / operand2;
            break;

        //mutliply  operation
        case '*':
            result = operand1 * operand2;
            break;

        //modulo  operation
        case '%':
            result = fmod(operand1,operand2) ;
            break; 
            
        //factorial  operation
        case '!':
            // Check if the operand is negative
            if (operand1 < 0){
                printf("Error! Factorial of a negative number doesn't exist.");
            }
            else {
                // Calculate the factorial of the operand
                for (int i = 1; i <= operand1; i++) {
                    result *= i;
                    
                }
            }
            break;
        
        // exponentiation operation
        case '^':
            result=pow(operand1,operand2);
            break;
    }

    // Return the result of the operation
    return result;
    }

// function counts given number
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

// function displays number as Scientific or Integer format
void display(char format, int m, int n,double operand1, double operand2, double result,char operator){

    // local variable for scientific shows
    int e=0;
    double temp_result1;
    long int temp_result2;
    int digit_int = digit_counter(result); // digit of int part of results

    // if format is scientific shows
    if(format=='S' || format =='s'){

        // expands result according to entered m number , to show as desired 
        for(int i=0;i<m-digit_int;i++){
            result = result*10;
            e--;
        }

        // assing double result to int temp_result2 
        temp_result2 = result;

         // checks result to avoid IEEE-754 Floating Point store problem
        if(temp_result2%10000==9999){
            temp_result2=temp_result2+1;
        }

        // deletes all zero at the end and increase e number 
        while(temp_result2%10==0 && temp_result2 != 0){
            temp_result2 = temp_result2/10;
            e++;
            
        }

        // make fit to show accoring to n number 
        result = temp_result2/pow(10,n);
        e = e+n;

        // if operator isn't factorial
        if(operator != '!'){
            printf("%lf %c %lf = ",operand1,operator,operand2); // prints first part of presentation of result
            printf("%0*.*lfe%d \n",m+1,n,result,e);               // prints second part of presentation of result  (after equal sign)
        }
  
        else{
            printf("%.0lf%c = ",operand1,operator);
            printf("%0*.*lfe%d\n",m+1,n,result,e);
        }
   
    }

    else if(format=='I' || format =='i'){

        // if operator isn't factorial
        if(operator != '!'){
             printf("%.0lf %c %.0lf = %.0lf\n",operand1,operator,operand2,result); // prints presentation of result
        }
        else{
            printf("%.0lf%c = %.0lf\n",operand1,operator,result);              // prints presentation of result if operator is factorial
        }
       
    }
}

/*
 *function  prompts the user to enter two numbers and an operator (+, -, *, /,!,^,%).
 * Before enter two numbers and operator, you need to enter format of output(result).
 * There are 2outputs for the enhanced calculator: “S” and “I”.
*/ 
void part2(){
    //variable for calculation and display
    char format; // S or I
    int m;      // all digit of result
    int n;      // float-part digit of result
    char operator;  // operator (+, -, *, /,!,^,%)
    double operand1;     
    double operand2;
    double result;  

    // the menu of calculation to look please compile and run code.
    printf("***************************\n");
    printf("enter the format of output (S and I): ");
    scanf(" %c",&format);

    // if user wants to scientific presentatiton, gets m and n  value 
    if(format=='S' || format=='s'){
        printf("enter m and n values: ");
        scanf("%d %d",&m,&n);

        // warn if n is greater than m
        while(m<n){
            printf("n can not be greater than m, Please enter another m and n values: ");
            scanf("%d %d",&m,&n);
        }
        
    }

    // scan operator
    printf("enter the operation(+,-,/,*,%%,!,^): ");
    scanf(" %c",&operator);
    while(operator != '+' && operator != '-' && operator != '/' && operator != '*'&& operator != '%' && operator != '!' && operator != '^'){
        printf("Please enter invalid operation(+,-,/,*,%%,!,^): ");
        scanf(" %c",&operator);

    }  
    // if operator isn't factorial scan 2 number 
    if(operator != '!'){
        
        printf("enter the first operand: ");
        scanf("%lf",&operand1);
        printf("enter the second operand: ");
        scanf("%lf",&operand2);
    }
     // if operator is factorial scan 1 number 
    else{
        printf("enter the operand: ");
        scanf("%lf",&operand1);
        operand2=0;
    }
    // send numbers to calculation function and assing to result . More detail look at calculation function
    result = calculation(operator, operand1, operand2);

    //prints outputs of result more detail look at display function
    display(format, m, n, operand1, operand2, result,operator);

}

float calculate_grade(float exam1 ,float exam2 ,float exam3,float assign1,float assign2){

    // sum exams and assingments
    float sum_exam = exam1+ exam2 + exam3;
    float sum_assign = assign1 + assign2;

    float final_grade; //to hold final grade

    final_grade = (sum_exam/3)*0.6 + (sum_assign/2)*0.4; // calculate final grade 	 60 percentage of  exams and 40 percentage of assingment

    return final_grade;
}

void part3(){
    //variables of exams
    float exam1;
    float exam2;
    float exam3;
    //variables of assingment
    float assign1;
    float assign2;

    float final_grade;

    // prompts and gets exam grades 
    printf("***************************\n");
    printf("Enter 3 exam grades of student: ");
    scanf("%f %f %f",&exam1,&exam2,&exam3);

    // if user enters exam grade over 100, warn user
    while (exam1>100 || exam2 > 100|| exam3 >100 ){
        if (exam1>100){
            printf("enter first exam grade below or equal 100: ");
            scanf("%f",&exam1);
        }
        if (exam2>100){
            printf("enter second exam grade below or equal 100: ");
            scanf("%f",&exam2);
        }
        if (exam3>100){
            printf("enter third exam grade below or equal 100: ");
            scanf("%f",&exam3);
        }
       
    }
    
     // prompts and gets assingment grades 
    printf("Enter 2 assignment grades of student: ");
    scanf("%f %f",&assign1,&assign2);

     // if user enters assingment grade over 100, warn user
    while(assign1>100 || assign2>100){
        if (assign1>100){
            printf("enter first assignment grade below or equal 100: ");
            scanf("%f",&assign1);
        }
        if (exam2>100){
            printf("enter second assignment grade below or equal 100: ");
            scanf("%f",&assign2);
        }
    }

    // calcalate final grade according to exams and assingment. more info look at calculate_grade function
    final_grade =  calculate_grade(exam1,exam2,exam3,assign1,assign2);
    printf("final grade: %.2f ",final_grade);

    // if final grade is less than 60 prints failed 
    if(final_grade<60){
        printf("Failed!");
    }
    // if final grade is equal or greater than 60 prints passed
    else{
        printf("Passed!");
    }
    printf("\n") ;   
}



