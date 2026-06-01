/* 
 * This program asks the user for a positive integer
 * and prints its prime factorization from smallest to largest factor,
 * separated by " * ". 
*/

#include <stdio.h>

/* Recursive function that prints all prime factors of input x */
void calcPrimeFactor (int x) {
    
    if (x == 1) {
        return;
    }

    int factor = 2;

    while (factor <= x) {
        if (x % factor == 0) {
            printf ("%d", factor);
            break;
        } else {
            factor++;
        }
    }
    if (x / factor > 1) {
        printf(" * ");
    }

    calcPrimeFactor (x / factor);
}

int main () {
    char s[100];
    int x;

    /* Read an integer from the user */
    printf ("Enter a number: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    /* Display error message if input is invalid */
    if (x <= 1) {
        printf("Please enter a number greater than 1.\n");
    }
    else {
        /* Using recursion to get all prime factors */
        printf ("The prime factors are ");
        calcPrimeFactor(x);
        printf ("\n");    
    }

    fgets(s,100,stdin);
    return 0;
}