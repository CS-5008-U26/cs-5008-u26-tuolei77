/* This program 
*/

#include <stdio.h>

int main () {
    char s[100];
    int x;
    int total = 0;

    /* Read an integer from the user */
    printf ("Enter a number: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    while (x > 0) {
        total += x % 10;
        x /= 10;
    }

    printf("The sum of the digits is %d\n", total);
    
    fgets(s,100,stdin);
}