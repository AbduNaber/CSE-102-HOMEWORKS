#include <stdio.h>

void part1(){

    int number;
    printf("***************************\n");
    printf("Please enter a year: ");
    scanf("%d",&number);

    if (number%400==0){
        printf("%d is  a leap year",number);
    }

    else if (number%4==0 && number%100 != 0){
        printf("%d is  a leap year",number);
    }
    else {
        printf("%d is not a leap year",number);
    }
}

void calculation(char format, int m, int n, char operator, int operand1, int operand2){
    
}



void part2(){

    char format;
    int m;
    int n;
    char operator;
    int operand1;
    int operand2;

    printf("***************************\n");
    printf("enter the format of output (S and I): ");
    scanf("%c",&format);
    f(format=='S'){
        printf("enter m and n values: ");
        scanf("%d %d",&m,&n);
    }
    printf("enter the operation(+,-,/,*,%%,!,^): ");
    scanf("%c",&operator);

    if(operator!='!'){
        
        printf("enter the first operand: ");
        scanf("%d",&operand1);
        printf("enter the second operand: ");
        scanf("%d",&operand2);
    }
    else{
        printf("enter the operand: ");
        scanf("%d",&operand1);
    }

    calculation(format,m,n,operator,operand1,operand2);


}





float calculate_grade(  float exam1 ,float exam2 ,float exam3,float assign1,float assign2){

    float sum_exam = exam1+ exam2 + exam3;
    float sum_assign = assign1 + assign2;

    float final_grade;

    final_grade = (sum_exam/3)*0.6 + (sum_assign/2)*0.4;

    return final_grade;
}


void part3(){

    float exam1;
    float exam2;
    float exam3;

    float assign1;
    float assign2;

    float final_grade;

    printf("***************************\n");


    printf("Enter 3 exam grades of student: ");
    scanf("%f %f %f",&exam1,&exam2,&exam3);

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
    

    printf("Enter 2 assignment grades of student: ");
    scanf("%f %f",&assign1,&assign2);

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



    final_grade =  calculate_grade(exam1,exam2,exam3,assign1,assign2);
    printf("final grade: %.2f ",final_grade);

    if(final_grade<60){
        printf("Failed!");
    }
    else{
        printf("Passed!");
    }
        

}
int main(){
    part3();
}