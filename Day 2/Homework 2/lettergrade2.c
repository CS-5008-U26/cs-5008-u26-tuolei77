/* This program asks the user for a number score between 0 and 100
 * and prints the corresponding letter grade.
 */

#include <stdio.h>
#include <string.h>

int main () {
    char s[100];
    int x;
    int remainder;
    char symbol[2];
    
    /* Read an integer from the user */
    printf ("Enter the number score between 0 and 100: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    /* Print score based on if-else condition
     * Print an error message if input is out of bound.
     */
    if (x < 0 || x > 100) {
        printf ("Your input is invalid. Please enter a number score between 0 and 100.\n");
    } else if (x <= 60) {
        printf ("Your letter grade is F.\n");
    } else {
        remainder = x % 10;
        if (remainder >= 1 && remainder <= 3) {
            strcpy(symbol, "-");
        } else if (remainder >= 4 && remainder <= 7){
            strcpy(symbol, "");
        } else {
            strcpy(symbol, "+");
        }
        if (x <= 70) {
            printf ("Your letter grade is D%s\n", symbol);
        } else if (x <= 80) {
            printf ("Your letter grade is C%s\n", symbol);
        } else if (x <= 90) {
            printf ("Your letter grade is B%s\n", symbol);
        } else {
            printf ("Your letter grade is A%s\n", symbol);
        }
    }

    fgets(s,100,stdin);
    return 0;
}