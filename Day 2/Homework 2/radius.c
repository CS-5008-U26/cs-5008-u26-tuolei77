/* This program accepts an integer from the user, and prints an integer approximation
 * to the area of a circle whose radius is the given integer. 
 */

#include <stdio.h>
#include <math.h>

int main () {
    char s[100];
    double PI = acos(-1);
    int radius;
    int area;

    /* Read an integer from the user */
    printf ("Enter an integer radius: ");
    scanf("%d", &radius);  
    fgets(s,100,stdin);

    /* Calculate the area */
    area = (int)(PI * radius * radius);

    /* Display final result on the screen */
    printf ("For a circle of radius %.1f the area is %d\n", (double)radius, area);

    fgets(s, 100, stdin);
    return 0;
}