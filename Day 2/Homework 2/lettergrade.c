/* This program asks the user for a number score between 1 and 10
 * and prints the corresponding letter grade.
*/

#include <stdio.h>

int main () {
    char s[100];
    int x;
    
    /* Read an integer from the user */
    printf ("Enter the number score between 1 and 10: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    /* Print score based on if-else condition
     * Print an error message if input is out of bound.
     */
    if (x < 1 || x > 10) {
        printf ("Your input is invalid. Please enter a number score between 1 and 10.\n");
    } else if (x <= 3) {
        printf ("Your letter grade is F.\n");
    } else if (x <= 5) {
        printf ("Your letter grade is E.\n");
    } else if (x == 6) {
        printf ("Your letter grade is D.\n");
    } else if (x == 7) {
        printf ("Your letter grade is C.\n");
    } else if (x == 8) {
        printf ("Your letter grade is B.\n");
    } else {
        printf ("Your letter grade is A.\n");
    }

    fgets(s,100,stdin);
    return 0;
}