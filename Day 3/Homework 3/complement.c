/* This program asks the user for a non-negative integer
 * and prints its 10's complement by substituting each digit d
 * with 9 - d, using a recursive function.
*/

#include <stdio.h>

/* Recursive function that calculates the 10's complement
 * of a non-negative integer x.
 */
int calcComplement(int x) {
    if (x / 10 == 0) {
        return 9 - x % 10;
    }

    return 10 * calcComplement(x / 10) + (9 - x % 10);

}

int main () {
    char s[100];
    int x;
    
    /* Keep asking until user enters a valid non-negative integer */
    while(1) {

        printf ("Enter an integer: ");
        scanf("%d", &x);  
        fgets(s,100,stdin);

        if (x >= 0) {
            printf("The complement is %d\n", calcComplement(x));
            break;
        }

        printf ("Please enter a valid integer greater than or equal to 0.\n");

    }
    
    fgets(s,100,stdin);
    return 0;
}