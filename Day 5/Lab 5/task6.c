#include <stdio.h>

int main (int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    if (argc > 1) {
        FILE *f = fopen (argv[1], "r");

	    if (f == NULL) {
            printf("No file exists!");
        }
	    else {
            char buffer[1000];
            while (fgets(buffer, 1000, f) != NULL) {
                printf("%s", buffer);
            }
            fclose(f);
	    }
    }
    return 0;
}