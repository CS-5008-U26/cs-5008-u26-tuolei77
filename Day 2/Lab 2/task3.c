/* This program 
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

int main () {
    char s[100];
    clock_t start_time = clock();

    printf("%d\n", 2);
    for (int x = 3; x <= 100; x+=2) {
        int is_prime = 1;  // 1 means true, assume x is prime first
        int sqrtX = (int)sqrt((double)x);
        for (int j = 3; j <= sqrtX; j+= 2) {
            if (x % j == 0) {
                is_prime = 0;  // x is not prime
                break;
            }
        }

        if (is_prime) {
            printf("%d\n", x);
        }
    }
    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    fgets(s, 100, stdin);
    return 0;
}