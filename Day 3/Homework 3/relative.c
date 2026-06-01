/* This program accepts an integer n, then prints the ET-function
 * for each integer from 2 to n.
 */

#include <stdio.h>

/* ET-function that calculates the number of integers less than x
 * that are relatively prime with x.
 */
int et(int x) {

    int cnt = 0;

    /* Check every positive integer less than x */
    for (int i = 1; i < x; i++) {

        int relative_prime = 1;

        /* Look for a common factor greater than 1 */
        for (int j = 2; j <= i; j++) {
            if (x % j == 0 && i % j == 0) {
                relative_prime = 0;
            }
        }
        if (relative_prime == 1) {
            cnt++;
        }
    }

    return cnt;
}



int main () {
    char s[100];
    int x;
    
    /* Keep asking until user enters a valid integer */
    while(1) {

        printf ("Enter an integer: ");
        scanf("%d", &x);  
        fgets(s,100,stdin);
        
        if (x >= 2) {
            /* Print ET-function for every integer from 2 to x. */
            for (int k = 2; k <= x; k++) {
                printf("ET-function for %d is %d\n", k, et(k));
            }
            break;
        }

        printf ("Please enter a valid integer greater than or equal to 2.\n");

    }
    
    fgets(s,100,stdin);
    return 0;
}