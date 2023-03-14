#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    if(denominator==0){
        printf("undefined answer");
    }
    else if (numerator==0){
        printf("0");
    }
    
    else{
        printf("%d//%d", numerator, denominator);
    }
    
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */


/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {

    /* if n bigger than d , count  from d until both of them divided*/
    if(*n>*d){ 
        for(int i=*d;i>=2;i--){
            if(*n%i==0 && *d%i==0 ){
                *n=*n/i;
                *d=*d/i;
                i=0;
            }
        }
    }

    /* if d bigger than or equal  n, count  from n until both of them divided*/
    else{ 
         for(int i=*n;i>=2;i--){
            if(*n%i==0 && *d%i==0){
               *n=*n/i;
               *d=*d/i; 
               i=0;
            }
    }
    }
} /* end fraction_simplify */
