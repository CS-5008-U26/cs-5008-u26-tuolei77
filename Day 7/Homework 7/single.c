/* This program reads the first 20 cities from uscities.csv into a
 * single linked list, and enables actions including size, delete,
 * reverse, get (move to front), or print cities in the list.
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
    char *FIPS;
    char *countyName;
    double latitude;
    double longitude;
    int population;

} city;

/* Create a struct to store node */
typedef struct singleNode {

    void *data;
    struct singleNode *next;

} sNode;

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

/* Create a node whose data field points to the given city */
sNode *createNode (city *x) {

    sNode *p = malloc(sizeof(sNode));
    p->data = x;
    p->next = NULL;
    return p;

}

/* Add a new node to the front of the list */
sNode *addToFront (city *x, sNode *head) {

    sNode *new = createNode(x);
    new->next = head;
    return new;

}

/* Add a new node to the end of the list */
sNode *addToEnd (city *x, sNode *head) {

    sNode *newNode = createNode(x);
    if (head == NULL) return newNode;

    sNode *curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;

}

/* Return a pointer to the nth node in the list */
sNode *getNode(int n, sNode *head) {
    
    if (n < 0 || head == NULL) return NULL;
    int len = 0;
    sNode *curr = head;
    while (len != n) {
        if (curr == NULL) return NULL;
        curr = curr->next;
        len++;
    }
    return curr;

}

/* Remove the given target node from the list and free it */
sNode *deleteNode(sNode *head, sNode *target) {

    if (head == NULL || target == NULL) return head; 
    if (head == target) {
        sNode *newHead = head->next;
        free(target);
        return newHead;
    }
    sNode *curr = head;
    while (curr->next != NULL && curr->next != target) {
        curr = curr->next;
    }
    if (curr->next == target) {
        curr->next = target->next;
        free(target);
    }
    return head;

}

/* Count and return the number of nodes in the list */
int getLength(sNode *head) {

    int len = 0;
    sNode *curr = head;
    while (curr != NULL) {
        curr = curr->next;
        len++;
    }
    return len;

}

/* Reverse the order of nodes in the list */
sNode *reverse(sNode *head) {

    sNode *curr = head;
    sNode *reversed = NULL;
    while (curr != NULL) {
        sNode *next = curr->next;
        curr->next = reversed;
        reversed = curr; 
        curr = next; 
    }
    return reversed;
}

/* Move the nth node to the front of the list */
sNode *moveToFront(int n, sNode *head) {

    sNode *target = getNode(n, head);
    if (target == NULL) return head;

    /* Save the city pointer before deleting the old node */
    city *c = (city *)target->data; 
    head = deleteNode(head, target);
    head = addToFront(c, head);
    
    return head;
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
            case 5: c->FIPS = strdup(fieldBuffer); break;
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

/* Read the first 20 cities from the given file into a Linked List */
sNode* readCityList (char *filename) {
    
    FILE *f = fopen(filename, "r");

    /* Check if the file can be opened */
    if (f == NULL) {
        printf("File does not exist!\n");
        return NULL;
    }

    char buffer[20000];
    sNode *head = NULL;

    /* Throw away the header line */
    fgets(buffer, 20000, f);

    /* Read the first 20 city records */
    for (int i = 0; i < 20; i++) {
        fgets(buffer, 20000, f);
        killNewline(buffer);
        city *c = stringToCity(buffer);
        head = addToEnd(c, head);
    }

    fclose(f);
    return head;
}

/* Free one city struct and its dynamically allocated string fields */
void freeCity (city *c) {
    free(c->name);
    free(c->nameASCII);
    free(c->postalCode);
    free(c->stateName);
    free(c->FIPS);
    free(c->countyName);
    free(c);
}

int main () {

    /* Read the first 20 cities from the file */
    sNode *cityList = readCityList("uscities.csv");

    /* Exit the program if the file could not be read */
    if (cityList == NULL) {
        return 1;
    }

    /* Ask the user to enter an action and respond accordingly */
    char buffer[100];
    while (1) {
        printf("size, delete, reverse, get, or print: ");
        fgets(buffer, 100, stdin);
        killNewline(buffer);

        if (strcmp(buffer, "size") == 0) {

            int len = getLength(cityList);
            printf("Size is %d\n", len);

        } else if (strcmp(buffer, "delete") == 0) {

            printf("Enter a number: ");
            fgets(buffer, 100, stdin);
            int num = atoi(buffer);

            if (num <= 0 || num > getLength(cityList)) {
                printf("The number is invalid!\n");
            } else {
                sNode *target = getNode(num - 1, cityList);
                city *c = (city *)target->data;
                cityList = deleteNode(cityList, target);  
                freeCity(c);              
            }

        } else if (strcmp(buffer, "reverse") == 0) {

            cityList = reverse(cityList);

        } else if (strcmp(buffer, "get") == 0) {

            printf("Enter a number: ");
            fgets(buffer, 100, stdin);
            int num = atoi(buffer);

            if (num <= 0 || num > getLength(cityList)) {
                printf("The number is invalid!\n");
            } else {
                cityList = moveToFront(num - 1, cityList);
            }
        } else if (strcmp(buffer, "print") == 0) {

            printf("Enter a number: ");
            fgets(buffer, 100, stdin);
            int num = atoi(buffer);

            if (num <= 0 || num > getLength(cityList)) {
                printf("The number is invalid!\n");
            } else {
                int i = 0;
                sNode *curr = cityList;
                while (i < num) {
                    city *c = (city *)curr->data;
                    printf("%s %s, population %d\n", c->name, c->postalCode, c->population);
                    curr = curr->next;
                    i++;
                }
            }
        } else {
            break;
        }
    }

    /* Free all remaining nodes and their city data before exiting */
    sNode *curr = cityList;
    while (curr != NULL) {
        sNode *next = curr->next;
        freeCity((city *)curr->data);
        free(curr);
        curr = next;
    }

    return 0;
}