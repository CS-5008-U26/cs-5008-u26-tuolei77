/* 
 * Priority queue implemented using a sorted array.
 * Enqueue: add n random numbers, and resort the whole array with quicksort.
 * Dequeue: remove n numbers from the front (lowest values), shifting the rest left.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100        // max number of elements to print
#define MAX_VALUE 100000000     // max value in randomly generated data

int *pq = NULL;
int pqsize = 0;
int pqcapacity = 0;

/* Y O U R   S O R T   F U N C T I O N */

/* This function does quick sort */
void quicksort_helper (int a[], int start, int end) {
    
    if (start >= end) return;

    /* The last element is pivot */
    int pivot = a[end];
    /* Separator is the limit, left than separator are the elements */
    /* smaller than pivot */
    int separator = start - 1;

    for (int i = start; i < end; i++) {
        /* If current element is smaller than pivot, move it to */
        /* the left */
        if (a[i] < pivot) {
            separator++;
            int temp = a[i];
            a[i] = a[separator];
            a[separator] = temp;
        }
        /* If current element is larger than pivot, do nothing */        
    }

    /* a[start to separator] are elements smaller than pivot thus */
    /* pivot should be in position separator + 1 */
    int temp = a[end];
    a[end] = a[separator + 1];
    a[separator + 1] = temp;

	quicksort_helper (a, start, separator);
	quicksort_helper (a, separator+2, end);
}

void sortarray (int a[], int n) {

    /* program your sort here */
    /* Quick Sort */
    quicksort_helper(a, 0, n - 1);

}

/* U T I L I T Y   F U N C T I O N S */

// printarray = print an array of ints
// a is the array, n is the number of elements

void printarray(int a[], int n) {
    int numberToPrint = ((n < MAX_TO_PRINT) ? n : MAX_TO_PRINT);
    for (int i=0; i < numberToPrint; i++) {
        printf ("%d ", a[i]);
    }
    printf ("\n");
}

// genarray - return an array of random ints on the heap
// numberofelements is how many elements in the array
// the array is returned
// don't forget to free the array when you are finished using it

int *genarray(int numberofelements) {
    int *result = malloc (numberofelements * sizeof(int));
    if (result == NULL) {
        printf ("malloc failed");
    } else {
        // fill the result array with random numbers between 0 and MAX_VALUE
        for (int i=0; i<numberofelements; i++) {
            // we have a problem
            // On Windows the rand() function only gives a 15-bit random number
            // This will be between 0 and 32767
            // So we will fix this with a crude trick
            // We will generate two random numbers, one for the high-order bits and the other
            // for the low-order 14 bits
            long long int r1 = rand();
            long long int r2 = rand();
            long long int randomValue = (r1 << 14) + (r2 & 0x3fff);
            result[i] = (int)(randomValue % MAX_VALUE);
        }
    }   
    return (result);
}

// ensure the capacity
void pqensurecapacity(int needed) {
    int newcapacity;
    if (needed > pqcapacity) {
        newcapacity = needed;

        int *newpq = malloc(newcapacity * sizeof(int));
        if (newpq == NULL) {
            printf ("malloc failed\n");
            return;
        }
        for (int i = 0; i < pqsize; i++) {
            newpq[i] = pq[i];
        }
        free(pq);
        pq = newpq;
        pqcapacity = newcapacity;
    }
}

// enqueue: add n random numbers to the queue, then re-sort the whole array
void pqenqueue(int n) {
    if (n == 0) return;
    // make sure there is enough room for the new numbers
    pqensurecapacity(pqsize + n);
    if (pqcapacity < pqsize + n) {
        return;
    }
    int *temp = genarray(n);
    if (temp == NULL) {
        printf ("malloc failed\n");
        return;
    }
    // copy the new numbers to the end of the priority queue
    for (int i = 0; i < n; i++) {
        pq[i + pqsize] = temp[i];
    }
    pqsize += n;
    free(temp);
    // resort the array
    sortarray(pq, pqsize);
}

// dequeue: remove and print up to n numbers from the front
void pqdequeue(int n) {
    // don't try to remove more numbers than we have
    if (n > pqsize) {
        n = pqsize;
    } 
    for (int i = 0; i < n; i++) {
        printf ("%d ", pq[i]);
    } 
    // shift the remaining elements to the front of the array
    for (int i = 0; i < pqsize - n; i++) {
        pq[i] = pq[n + i];
    }
    printf ("\n");
    pqsize -= n;
    return;
}

// timedsort - runs a sort and records the elapsed time
// a is the array, n is how many elements

void timedsort (int n) {
    clock_t startTime = clock();        // get the start time
    pqenqueue(n);
    clock_t endTime = clock();          // get the end time
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf ("Elapsed time: %f seconds\n\n", elapsedTime);   // print the elapsed time
}

// timedsort - runs a sort and records the elapsed time
// a is the array, n is how many elements

void timeddequeue(int n) {
    clock_t startTime = clock();        // get the start time
    pqdequeue(n);
    clock_t endTime = clock();          // get the end time
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf ("Elapsed time: %f seconds\n\n", elapsedTime);   // print the elapsed time
}

/* M A I N   F U N C T I O N */
void main () {
    char buffer[100];
    int nelements;

    srand(time(NULL));  // seed the random number generator

    // run timed sorts
    int keepgoing = 1;
    while (keepgoing) {

        printf ("How many numbers to add: ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            break;
        } else {
            nelements = atoi(buffer);
            if (nelements < 0) {
                printf ("Must be a nonnegative number of numbers\n");
            } else {
                // enqueue
                timedsort(nelements);
            }
        }

        printf ("How many numbers to remove: ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            break;
        } else {
            nelements = atoi(buffer);
            if (nelements < 0) {
                printf ("Must be a nonnegative number of numbers\n");
            } else {
                // deque
                timeddequeue(nelements);
            }
        }
    }
    free(pq);
}