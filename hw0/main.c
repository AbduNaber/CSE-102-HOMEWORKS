#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 13/11 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;
    /* A forth fractional number that taken from user */
    int num4, den4;
    /* A fifth fractional number that taken from user*/
    int num5, den5;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    
    printf("Enter numerator and denominator of forth number: ");
    /* get another denominator from user if den equal to 0*/
    scanf("%d %d", &num4,&den4);		// get forth fractional number that taken from user
        while(den4==0){
            printf("please enter another denominator number different from 0: ");
            scanf("%d",&den4);
        }
    /*end of getting*/

    printf("Enter numerator and denominator of fifth number: ");
    scanf("%d %d", &num5,&den5);  		// get fifth fractional number that taken from user

    /* get another denominator from user if den equal to 0*/
    while(den5==0){
            printf("please enter another denominator number different from 0: ");
            scanf("%d",&den5);
        }
    /*end of getting*/
    
    fraction_add(num4, den4, num5, den5, &num3, &den3);
    printf("Addition: ");
    fraction_print(num3, den3);
    printf(" \n");
    
    fraction_sub(num4, den4, num5, den5, &num3, &den3);
    printf("Subtraction: ");
    fraction_print(num3, den3);
    printf(" \n");
       
    fraction_mul(num4, den4, num5, den5, &num3, &den3);
    printf("Multiplication: ");
    fraction_print(num3, den3);
    printf(" \n");
    fraction_div(num4, den4, num5, den5, &num3, &den3);
    printf("Division: ");
    fraction_print(num3, den3);
    printf(" \n");

    return(0);
}
