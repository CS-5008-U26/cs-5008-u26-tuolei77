/* sort template
 *
  * you can copy this template to program a new sorting technique
  * 
  * there are some useful utility functions
  * the main function has everything you need
  * * some test cases
  * * a loop to try timed sorting
  * 
  * you just need to fill in the sortarray() function
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100        // max number of elements to print
#define MAX_VALUE 100000000     // max value in randomly generated data

/* T E S T   C A S E   D A T A */

int test1[] =       { 3 };
int expected1[] =   { 3 };
int n1 =            1;
int test2[] =       { 5, 3 };
int expected2[] =   { 3, 5 };
int n2 =            2;
int test3[] =       { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int expected3[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n3 =            10;
int test4[] =       { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
int expected4[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n4 =            10;
int test5[] =       { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };
int expected5[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n5 =            10;
int test6[] =       { 1, 2, 3, 2, 2 };
int expected6[] =   { 1, 2, 2, 2, 3 };
int n6 =            5;

/* H E L P E R   F U N C T I O N S */
/* Create a struct to store node */
typedef struct treeNode {
    int value;
    struct treeNode *left;
    struct treeNode *right;
} tNode;

/* Create a new leaf node, like a constructor */
tNode *createTNode (int x) {
        tNode *t = malloc(sizeof(tNode));
        t->value = x;
        t->left = NULL;
        t->right = NULL;
        return t;
}

/* Insert into the BST rooted at t */
tNode *insertBST(tNode *t, int x) {
    
    /* Base case: we've reached an empty spot in the tree */
    if (t == NULL) {
        return createTNode(x);
    }

    /* x is smaller than the current node's value:
     * recurse into the left subtree */    
    if (x <= t->value) {
        t->left = insertBST(t->left, x);
    }
    /* x is larger than the current node's value:
     * same idea, but recurse into the right subtree */    
    else {
        t->right = insertBST(t->right, x);
    }
    /* Return the root of this subtree
     * so the recursive caller above can relink it */    
    return t;
}

void fillArray (tNode *t, int a[], int *index) {

    /* check if root is null */
    if (t == NULL) {

    } else {
        /* add left subtree */
        fillArray (t->left, a, index);

        /* add the value in root to the array */
        a[*index] = t->value;

        /* increase index */
        (*index)++;

        /* add right subtree */
        fillArray (t->right, a, index);
    }   
}

/* Free every tNode in the tree */
void freeTree (tNode *t) {
    if (t == NULL) {
        return;
    }
    freeTree(t->left);
    freeTree(t->right);
    free(t);
} 

/* Y O U R   S O R T   F U N C T I O N */

void sortarray (int a[], int n) {

    /* program your sort here */
    /* this is BST sort */
    tNode *t = createTNode (a[0]);  // create root node

    for (int i = 1; i < n; i++) {
        t = insertBST (t, a[i]);    // insert array values into BST
    }
    int index = 0;
    fillArray (t, a, &index);	// put the values back into the array

    /* Free trees and arrays */
   freeTree(t);
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

/* */

int *genarraysorted(int numberofelements) {
    int *result = malloc (numberofelements * sizeof(int));
    if (result == NULL) {
        printf ("malloc failed");
    } else {
        // fill the result array with sorted index
        for (int i=0; i<numberofelements; i++) {
            result[i] = i;
        }
    }   
    return (result);
}

/* */

int *genarrayreversed(int numberofelements) {
    int *result = malloc (numberofelements * sizeof(int));
    if (result == NULL) {
        printf ("malloc failed");
    } else {
        // fill the result array with reversed index
        for (int i=0; i<numberofelements; i++) {
            result[i] = numberofelements - i - 1;
        }
    }   
    return (result);
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

// timedsort - runs a sort and records the elapsed time
// a is the array, n is how many elements

void timedsort (int a[], int n) {
    clock_t startTime = clock();        // get the start time
    sortarray (a, n);
    clock_t endTime = clock();          // get the end time
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf ("Result: ");                // print the sorted data
    printarray(a, n);
    printf ("Elapsed time: %f seconds\n\n", elapsedTime);   // print the elapsed time
}

// testsort - runs a sort on a test case with known results
// a is the array, n is how many elements
// expected is the array with the expected correct values after sorting

void testsort (int a[], int n, int expected[]) {
    printf ("Test case: ");             // print the test data
    printarray(a, n);
    sortarray(a, n);
    printf ("Result: ");                // print the result of sorting
    printarray(a, n);
    int ok = 1;                         // print whether the result is correct
    for (int i=0; ok && (i<n); i++) {
        ok = (a[i] == expected[i]);
    }
    printf ("%s\n\n", (ok ? "PASSED" : "FAILED"));
}

/* M A I N   F U N C T I O N */
void main () {
    char buffer[100];
    int nelements;
    int maxvalue;
    int *randomdata;
    int *sorteddata;
    int *reverseddata;

    srand(time(NULL));  // seed the random number generator

    // run test cases
    testsort(test1, n1, expected1);
    testsort(test2, n2, expected2);
    testsort(test3, n3, expected3);
    testsort(test4, n4, expected4);
    testsort(test5, n5, expected5);
    testsort(test6, n6, expected6);

    // run timed sorts
    int keepgoing = 1;
    while (keepgoing) {
        printf ("How many elements for random data? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf ("Must be a positive number of elements\n");
            } else {
                randomdata = genarray(nelements);
                if (randomdata != NULL) {
                    timedsort(randomdata, nelements);
                    free (randomdata);
                }
            }
        }
    }

    // run sorted array
    keepgoing = 1;
    while (keepgoing) {
        printf ("How many elements for sorted data? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf ("Must be a positive number of elements\n");
            } else {
                sorteddata = genarraysorted(nelements);
                if (sorteddata != NULL) {
                    timedsort(sorteddata, nelements);
                    free (sorteddata);
                }
            }
        }
    }

    // run reversed array
    keepgoing = 1;
    while (keepgoing) {
        printf ("How many elements for reversed data? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf ("Must be a positive number of elements\n");
            } else {
                reverseddata = genarrayreversed(nelements);
                if (reverseddata != NULL) {
                    timedsort(reverseddata, nelements);
                    free (reverseddata);
                }
            }
        }
    }
}