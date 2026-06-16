#include <stdio.h>

int main () {

    char inputBuffer [200];

    inputBuffer[0] = 'X';        // so we will do the loop at least once

    while (inputBuffer[0] != '\n') {

        printf("Enter a string: ");

        fgets(inputBuffer,200,stdin);

        if (inputBuffer[0] != '\n') {
        
            printf("%s", inputBuffer);
        
        }
    }
    return 0;
}