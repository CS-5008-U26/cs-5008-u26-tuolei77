/* This program asks the user for a number score between 1 and 10
 * and prints the corresponding letter grade using a switch statement.
*/

#include <stdio.h>

int main () {
    char s[100];
    int x;
    
    /* Read an integer from the user */
    printf ("Enter the number score between 1 and 10: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    /* Print score based on switch statement
     * Print an error message if input is out of bound.
     */
    switch (x) {
        case 1:
        case 2:
        case 3:
            printf ("Your letter grade is F.\n");
            break;
        case 4:
        case 5:
            printf ("Your letter grade is E.\n");
            break;
        case 6:
            printf ("Your letter grade is D.\n");
            break;
        case 7:
            printf ("Your letter grade is C.\n");
            break;
        case 8:
            printf ("Your letter grade is B.\n");
            break;
        case 9:
        case 10:
            printf ("Your letter grade is A.\n");
            break;
        default:
            printf ("Your input is invalid. Please enter a number score between 1 and 10.\n");
            break;
        }

    fgets(s,100,stdin);
    return 0;
}