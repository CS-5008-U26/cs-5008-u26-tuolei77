/* This program accepts an integer from the user, and prints an integer approximation
 * to the area of a circle whose radius is the given integer. 
 */

#include <stdio.h>


int isHarshad (int x) {
    int total = 0;
    int original = x;
    while (x > 0) {
        total += x % 10;
        x = x / 10;
    }
    return (original % total == 0);

}

int main () {
    char s[100];
    int y = 10;

    while (y < 100) {
        if (isHarshad(y)) {
            printf ("%d\n", y);
        } 
        y += 1;
    }
    
    fgets(s, 100, stdin);
    return 0;
}