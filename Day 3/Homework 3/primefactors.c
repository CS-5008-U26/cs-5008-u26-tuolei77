/* 
 * This program asks the user for a positive integer
 * and prints its prime factorization from smallest to largest factor,
 * separated by " * ". 
*/

#include <stdio.h>

int main () {
    char s[100];
    int x;
    int factor = 2;
    int cnt = 0;

    /* Read an integer from the user */
    printf ("Enter a number: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    /* Display error message if input is invalid */
    if (x <= 1) {
        printf("Please enter a number greater than 1.\n");
    }
    else {
        /* Using loops to get all prime factors */
        printf ("The prime factors are ");
        while (factor <= x) {
            while (x % factor == 0) {
                
                /* check to ensure * is not printed for the first factor */
                if (cnt != 0) {
                printf (" * ");
                }
                printf ("%d", factor);
                x = x / factor;
                cnt = 1;
            }
            factor++;
        }
        printf ("\n");    
    }

    fgets(s,100,stdin);
    return 0;
}