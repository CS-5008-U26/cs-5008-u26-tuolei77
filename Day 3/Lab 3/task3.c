#include <stdio.h>
#include <time.h>

int fibonacci(int fibCounter, int fibOldResult, int fibOldOldResult) {
    if (fibCounter == 0 || fibCounter == 1) {
        return 1;
    }
    return fibOldResult + fibOldOldResult;
}

int main() {
    char s[100];

    int fibCounter = 0;
    int fibResult = 0;
    int fibOldResult = 0;
    int fibOldOldResult = 0;

    clock_t start = clock();

    while (1) {
        fibResult = fibonacci(fibCounter, fibOldResult, fibOldOldResult);

        printf("Fibonacci %d = %d\n", fibCounter, fibResult);

        fibOldOldResult = fibOldResult;
        fibOldResult = fibResult;
        fibCounter += 1;

        double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

        if (elapsed >= 5.0) {
            break;
        }
    }

    fgets(s, 100, stdin);
    return 0;
}