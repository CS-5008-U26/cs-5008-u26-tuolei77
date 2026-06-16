/* This program prints the size of a file in bytes. If the filename is not entered
 * as a command line argument, the program will ask user for it.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

/* Remove the newline from the end of a string, if there is one */
void killNewline (char *str) {

    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

/* Return the size of the input file, and -1 if file does not exist */
int getFileSize (char * input) {

	struct stat fileStat;

	if (stat(input, &fileStat) < 0) {
        switch (errno) {
            case ENOENT:
                printf("No such file as %s\n", input);
                break;
        }
        return -1;
	} 
    else {
		return fileStat.st_size;
	}
}

int main (int argc, char **argv) {
    
    char inputBuffer [200];
    char *f;

    /* Get filename from command line argument or user input */
    if (argc < 2) {

        printf("Enter the name of a file: ");
        fgets(inputBuffer,200,stdin);
        killNewline(inputBuffer);

        f = inputBuffer;
    }
    else {
        f = argv[1];
    }
    
    /* Display the size of the file */
    int fileSize = getFileSize(f);

    if (fileSize != -1) {
        printf("%s has %d bytes\n", f, fileSize);
    }       
    
    return 0;
}