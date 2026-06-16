#include <stdio.h>
#include <string.h>
#include <ctype.h>

void condition (char *in, char *out) {
    /*
    int j = 0;
    
    for (int i = 0; in[i] != '\0'; i++) {
        if(isalpha(in[i])) {
            out[j] = tolower(in[i]);
            j++;
        }
    }
    out[j] = '\0';
    */
    while(*in) {
        if(isalpha(*in)) {
            *out = tolower(*in);
            out++;
        }
        in++;
    }
    *out = '\0';
}

int main () {

    char inputBuffer [200];
    char converted [200];

    inputBuffer[0] = 'X';        // so we will do the loop at least once

    while (inputBuffer[0] != '\n') {

        printf("Enter a string: ");

        fgets(inputBuffer,200,stdin);

        if (inputBuffer[0] != '\n') {
        
            condition(inputBuffer, converted);
            printf("%s\n", converted);
        
        }
    }
    return 0;
}