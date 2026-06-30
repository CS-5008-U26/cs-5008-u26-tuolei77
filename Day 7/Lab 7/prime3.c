#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


typedef struct intNode {
    long long int value;
    struct intNode *next;
} node;

node *createNode (long long int x) {

    node *p = malloc(sizeof(node));
    p->value = x;
    p->next = NULL;
    return p;

}

int main () {
    char s[100];
    clock_t start_time = clock();
    long long int last_prime = 2;
    double timeLimit = 0.5;
    node *primes = createNode(2);
    node *tail = primes; 

    for (long long int x = 3; ; x += 2) {
        int is_prime = 1;  // 1 means true, assume x is prime first
        long long int sqrtX = (long long int)sqrt((double)x);

        node *current = primes;
        while (current != NULL && current->value <= sqrtX) {
            if (x % current->value == 0) {
                is_prime = 0;
                break;
            }
            current = current->next;
        }

        if (is_prime) {
            last_prime = x;

            node *newNode = createNode(x);
            tail->next = newNode;
            tail = newNode;

            // check time after each new prime found
            clock_t end_time = clock();
            double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            if (time_taken >= timeLimit) {
                break;
            }
        }
    
    }

    printf("Last prime found: %lld\n", last_prime);
    fgets(s, 100, stdin);
    return 0;
}