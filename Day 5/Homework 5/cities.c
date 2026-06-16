/* This program reads the first 20 cities from uscities.csv.
 * It prints the sum of their populations and the northernmost city.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

/* Get the next comma-separated field from start into out and
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

int main () {

    FILE *f = fopen ("uscities.csv", "r");

    /* Check if the file can be opened, if not display error message and return */
    if (f == NULL) {
        printf("File does not exist!\n");
    } 
    else {
        char buffer [20000];
        char cityName [1000];
        char latitudeStr [1000];
        char populationStr [1000];
        char skip [20000];
        char northernmostCity [1000];
        double maxLatitude = -90;
        double latitude;
        int totalPopulation = 0;

        /* Throw away the header line */
        fgets(buffer, 20000, f);

        /* Read the first 20 lines */
        for (int i = 0; i < 20; i++) {
            
            /* Read the line and remove newline character */
            fgets(buffer, 20000, f);
            killNewline(buffer);

            char *p = buffer;
            
            /* Skip column 1 */
            p = getNextField(p, ',', skip);  

            /* Get city name */
            p = getNextField(p, ',', cityName);

            /* Skip column 3 - 6 */
            int cnt = 3;
            while (cnt < 7) {
                p = getNextField(p, ',', skip);    
                cnt++;
            }

            /* Get latitude, and convert string to double */
            p = getNextField(p, ',', latitudeStr);  
            latitude = atof(latitudeStr);

            /* Find the largest latitude and record the city name */
            if (latitude > maxLatitude) {
                maxLatitude = latitude;
                strcpy(northernmostCity, cityName);
            }     

            /* Skip column 8 */
            p = getNextField(p, ',', skip); 

            /* Get population, convert to int and add it to total population */
            p = getNextField(p, ',', populationStr);   
            totalPopulation += atoi(populationStr);

        }

        printf("Sum of the populations: %d\n", totalPopulation);
        printf("Northernmost city is %s\n", northernmostCity);
        
        fclose(f);
    }
    return 0;
}