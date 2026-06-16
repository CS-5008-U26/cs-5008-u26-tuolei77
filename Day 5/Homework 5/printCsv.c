/* This program reads a CSV file and prints each line, followed by individual fields.
 * Each line and field is enclosed in > < brackets.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Remove the newline from the end of a string, if there is one */
void killNewline (char *str) {

    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
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

/* Extract the next comma-separated field from start into out and
 * return a pointer to the next field.
*/
char *getNextField (char *start, char separator, char *out) {

    /* Special case of no more fields */
    if (*start == '\0') {
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

int main () {

    char inputBuffer [200];

    /* Get the file name and remove the newline */
    printf("Enter the file name: ");

    fgets(inputBuffer,200,stdin);

    killNewline(inputBuffer);

    FILE *f = fopen (inputBuffer, "r");

    /* Check if the file can be opened */
    if (f == NULL) {
        printf("File does not exist!\n");
    } 
    else {
        char buffer[1000];
        char nextField [1000];
        
        /* Read the file line by line till the end */
        while (fgets(buffer, 1000, f) != NULL) {
            
            killNewline(buffer);
            printf(">%s<\n", buffer); 

            /* Split each line into fields by comma */
            char *p = buffer;
            while (p != NULL) {
                p = getNextField(p, ',', nextField);
                if (p != NULL){
                    printf(">%s<\n", nextField); 
                }                
            }
        }
        fclose(f);
    }
    return 0;
}