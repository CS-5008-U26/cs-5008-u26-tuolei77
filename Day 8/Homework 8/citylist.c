/* This program reads city data from uscities.csv.
 * It stores the cities in a vector, then uses BSTs to sort them
 * by latitude and FIPS code.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Create a struct to store city data */
typedef struct city_struct {

    char *name;
    char *nameASCII;
    char *postalCode;
    char *stateName;
    int FIPS;
    char *countyName;
    double latitude;
    double longitude;
    int population;

} city;

/* Create a struct to store vector */
typedef struct vector_s {

    int size;
    void **data;

} vector;

/* Create a struct to store node */
typedef struct treeNode {
    void *data;
    struct treeNode *left;
    struct treeNode *right;
} tNode;


/* Remove the newline from the end of a string, if there is one */
void killNewline (char *str) {
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* Remove quotes around a string, if there is one */
void killQuotes (char *str) {
    int len = strlen(str);

    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        str[len - 1] = '\0';
        memmove(str, str + 1, len - 1);
    }
}

/* Get the next separator-separated field from start into out and
 * return a pointer to the next field.
 */
char *getNextField (char *start, char separator, char *out) {

    /* Special case of no more fields */
    if (start == NULL || *start == '\0') {
        return NULL;
    }

    char *sepPointer = strchr(start, separator);

    /* No separator found, copy the rest of the string */
    if (sepPointer == NULL) {

        strcpy(out, start);
        killQuotes(out);
        return start + strlen(start);

    } else {

        /* Copy up to the separator, return pointer past it */
        strncpy(out, start, sepPointer - start);
        out[sepPointer - start] = '\0';
        killQuotes(out);
        return sepPointer + 1;

    }
}

/* Create a new vector with the given size */
vector *createVector (int size) {
	vector *v = malloc (sizeof(vector));
	v->size = size;
	v->data = malloc (size * sizeof(void *));
	return (v);
}

/* Append x to the end of the vector, and grow the vector size by 1 */
void insertLast (vector *v, void *x) {
    void **newData = malloc ((1 + v->size) * sizeof(void *));
    for (int i = 0; i < v->size; i++) {
        newData[i] = v->data[i];
    }
    newData[v->size] = x;
    v->size += 1;
    free (v->data);
    v->data = newData;
}

/* Return the number of elements in the vector */
int vectorSize (vector *v) {
	return (v->size);
}

/* Return the element stored at index i. */
void *vectorGet (vector *v, int i) {
	return (v->data[i]);
}

/* Create a new leaf node */
tNode *createTNode (void *x) {
        tNode *t = malloc(sizeof(tNode));
        t->data = x;
        t->left = NULL;
        t->right = NULL;
        return t;
}

/* Insert city x into the BST rooted at t, ordered by latitude */
tNode *insertBST(tNode *t, city *x) {

    if (t == NULL) {
        return createTNode(x);
    }
    city *current = (city *) t->data;
    if (x->latitude == current->latitude) return t;
    if (x->latitude < current->latitude) {
        t->left = insertBST(t->left, x);
    }
    else {
        t->right = insertBST(t->right, x);
    }
    return t;
}

/* Copy city pointers from the tree rooted at t into array a */
int fillArray (tNode *t, city **a, int start) {
    if (t == NULL) return start;
    int nextIndex = start;
    if (t->left != NULL) {
        nextIndex = fillArray (t->left, a, nextIndex);
    }
    a[nextIndex] = (city *)t->data;
    nextIndex++;
    if (t->right != NULL) {
        nextIndex = fillArray (t->right, a, nextIndex);
    }
    return (nextIndex);
}

/* Find city in the array by name using linear search */
int findByName (city **a, int n, char *target) {
    for (int i = 0; i < n; i++) {
        if (strcmp(a[i]->nameASCII, target) == 0) {
            return i;
        }
    }
    return -1;
}

/* Same as insertBST, but orders cities by county FIPS code */
tNode *insertFIPS(tNode *t, city *x) {

    if (t == NULL) {
        return createTNode(x);
    }
    city *current = (city *) t->data;
    if (x->FIPS == current->FIPS) return t;
    if (x->FIPS < current->FIPS) {
        t->left = insertFIPS(t->left, x);
    }
    else {
        t->right = insertFIPS(t->right, x);
    }
    return t;
}

/* Find city in the array by FIPS using binary search */
int findByFIPS (city **a, int start, int end, int target) {
    if (start > end) {
        return -1;
    }
    int mid = (start + end) / 2;

    if (target == a[mid]->FIPS) {
        return mid;
    }
    if (target < a[mid]->FIPS) {
        return findByFIPS(a, start, mid - 1, target);
    } else {
        return findByFIPS(a, mid + 1, end, target);
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

/* Convert one line of text from the CSV file into a city struct */
city *stringToCity (char *textLine) {

    char fieldBuffer[1000];
    char *p = textLine;
    int fieldNum = 0;
    city *c = malloc(sizeof(city));

    /* Read fields one at a time and store them in the city struct */
    while (p != NULL) {

        p = getNextField(p, ',', fieldBuffer);

        if (p == NULL) {
            break;
        }

        fieldNum++;

        switch (fieldNum) {
            case 1: c->name = strdup(fieldBuffer); break;
            case 2: c->nameASCII = strdup(fieldBuffer); break;
            case 3: c->postalCode = strdup(fieldBuffer); break;
            case 4: c->stateName = strdup(fieldBuffer); break;
            case 5: c->FIPS = atoi(fieldBuffer); break;
            case 6: c->countyName = strdup(fieldBuffer); break;
            case 7: c->latitude = atof(fieldBuffer); break;
            case 8: c->longitude = atof(fieldBuffer); break;
            case 9: c->population = atoi(fieldBuffer);
        }

        /* Stop after reading the first nine fields */
        if (fieldNum >= 9) {
            break;
        }
    }

    return c;
}

/* Read the first n cities from the given file into a vector */
vector* readCityList (char *filename, int n) {
    
    FILE *f = fopen(filename, "r");

    /* Check if the file can be opened */
    if (f == NULL) {
        printf("File does not exist!\n");
        return NULL;
    }

    char buffer[20000];
    vector *v = createVector(0);

    /* Throw away the header line */
    fgets(buffer, 20000, f);

    /* Read the first n city records */
    for (int i = 0; i < n; i++) {
        fgets(buffer, 20000, f);
        killNewline(buffer);
        city *c = stringToCity(buffer);
        insertLast(v, c);
    }

    fclose(f);
    return v;
}

/* Free one city struct and its dynamically allocated string fields */
void freeCity (city *c) {
    free(c->name);
    free(c->nameASCII);
    free(c->postalCode);
    free(c->stateName);
    free(c->countyName);
    free(c);
}

int main () {

    /* Task 1. */
    char buffer[100];

    printf("How many cities: ");
    fgets(buffer, 100, stdin);
    killNewline(buffer);
    int num = atoi(buffer);

    if (num <= 0) {
        printf("The number is invalid!\n");
        return 1;
    }

    /* Read the first n cities from the file */
    vector *cityVector = readCityList("uscities.csv", num);

    /* Exit the program if the file could not be read */
    if (cityVector == NULL) {
        return 1;
    }

    for (int i = 0; i < num; i++) {

        city *c = (city *)vectorGet(cityVector, i);

        printf("%s %s, population %d, at (%.4f, %.4f)\n",
            c->nameASCII, c->postalCode, c->population,
            c->latitude, c->longitude);
    }

    /* Task 2: build a BST ordered by latitude, change it into a sorted array 
     * using inorder traversal, then linearly search that array for New York. */
    tNode *root = NULL;
    city **cityArray = malloc(num * sizeof(city *));
    int element = 0;
    char *target = "New York";

    for (int i = 0; i < num; i++) {
        city *c = (city *)vectorGet(cityVector, i);
        root = insertBST(root, c);
    }

    int numLat = fillArray (root, cityArray, 0);	

    element = findByName(cityArray, numLat, target);

    if (element == -1) {
        printf("New York was not in the list\n");
    } else {
        printf("By latitude, New York is index %d\n", element);
    }


    /* Task 3: build a BST ordered by FIPS code, change it into a sorted array
     * , then binary search that array for FIPS 36081. */
    tNode *rootFIPS = NULL;
    city **cityArrayFIPS = malloc(num * sizeof(city *));
    int elementFIPS = 0;
    int targetNum = 36081;

    for (int j = 0; j < num; j++) {
        city *c = (city *)vectorGet(cityVector, j);
        rootFIPS = insertFIPS(rootFIPS, c);
    }

    int numFIPS = fillArray (rootFIPS, cityArrayFIPS, 0);	

    elementFIPS = findByFIPS(cityArrayFIPS, 0, numFIPS - 1, targetNum);

    if (elementFIPS == -1) {
        printf("Entry with FIPS code 36081 was not in the list\n");
    } else {
        city *found = cityArrayFIPS[elementFIPS];
        printf("By FIPS code, %s is index %d\n",found->nameASCII, elementFIPS);
    }

    /* Free trees and arrays */
    freeTree(root);
    freeTree(rootFIPS);

    free(cityArray);
    free(cityArrayFIPS);

    /* Free all cities in the vector, then free the vector itself */
    for (int i = 0; i < cityVector->size; i++) {
        city *c = (city *) vectorGet(cityVector, i);
        freeCity(c);
    }
    free(cityVector->data);
    free(cityVector);
    
    return 0;
}