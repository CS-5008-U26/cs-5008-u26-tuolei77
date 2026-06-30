/*
Task 2A. Calculate the first 100 prime numbers and put them into a linked list.  
Now make a new linked list that has only those prime numbers whose second digit is bigger than the first digit.  
Print this new list.
Task 2B.  Take this list and reverse it.  Print this new list.
*/

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
    long long int last_prime = 2;
    node *primes = createNode(2);
    node *tail = primes; 
    int cnt = 1;

    node *primes2 = NULL;
    node *tail2 = primes2; 

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
            cnt++;
            node *newNode = createNode(x);
            tail->next = newNode;
            tail = newNode;

            if (x > 9 && ((x/10)%10 < x%10)) {
                node *newNode2 = createNode(x);
                if (primes2 == NULL) {
                    primes2 = newNode2;
                    tail2 = newNode2;
                } else {
                    tail2->next = newNode2;
                    tail2 = newNode2;
                }
            }

            if (cnt > 100) {
                break;
            }
        }
    }

    node *curr = primes2;
    while (curr) {
        printf("%lld\n", curr->value);
        curr = curr->next; 
    }


    fgets(s, 100, stdin);
    return 0;
}