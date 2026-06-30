/* This program 
*/

#include <stdio.h>
#include <math.h>
#include <time.h>

int main () {
    char s[100];
    clock_t start_time = clock();
    long long int last_prime = 2;

    for (long long int x = 3; ; x += 2) {
        int is_prime = 1;  // 1 means true, assume x is prime first
        long long int sqrtX = (long long int)sqrt((double)x);

        for (long long int j = 2; j <= sqrtX; j++) {
            if (x % j == 0) {
                is_prime = 0;  // x is not prime
                break;
            }
        }

        if (is_prime) {
            last_prime = x;

            // check time after each new prime found
            clock_t end_time = clock();
            double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            if (time_taken >= 0.5) {
                break;
            }
        }
    
    }

    printf("Last prime found: %lld\n", last_prime);
    fgets(s, 100, stdin);
    return 0;
}