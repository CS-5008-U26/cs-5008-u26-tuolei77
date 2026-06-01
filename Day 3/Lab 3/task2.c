/* This program accepts an integer from the user, and prints an integer approximation
 * to the area of a circle whose radius is the given integer. 
 */

#include <stdio.h>
#include <time.h>

int fibonacci (int x) {
    if (x == 0 || x == 1) {
        return 1;
    }
    return fibonacci(x - 1) + fibonacci(x - 2);
}

int main () {
    char s[100];
    int y = 0;
    clock_t start_time = clock();

    while (1) {
        printf ("%d %d\n",y, fibonacci(y));
        y += 1;
        clock_t end_time = clock();
        double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        if (time_taken >= 5.0) {break;}
    }
    
    fgets(s, 100, stdin);
    return 0;
}