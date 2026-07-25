/* This program reads city data from uscities.csv and uses dynamic 
 * programming to find the set of cities with maximum total population 
 * whose total name length does not exceed 200 characters.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 200
#define MAX_LENGTH 200

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
    long long population;
    int length;
} city;

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

/* Convert one line of text from the CSV file into a city struct */
city *stringToCity (char *textLine) {

    char fieldBuffer[1000];
    char *p = textLine;
    int fieldNum = 0;
    city *c = malloc(sizeof(city));

    if (c == NULL) {
        return NULL;
    }

    /* Read fields one at a time and store them in the city struct */
    while (p != NULL) {

        p = getNextField(p, ',', fieldBuffer);

        if (p == NULL) {
            break;
        }

        fieldNum++;

        switch (fieldNum) {
            case 1: c->name = strdup(fieldBuffer); break;            
            case 2: c->nameASCII = strdup(fieldBuffer);
                    c->length = strlen(fieldBuffer);
                    break;            
            case 3: c->postalCode = strdup(fieldBuffer); break;
            case 4: c->stateName = strdup(fieldBuffer); break;
            case 5: c->FIPS = strdup(fieldBuffer); break;
            case 6: c->countyName = strdup(fieldBuffer); break;
            case 7: c->latitude = atof(fieldBuffer); break;
            case 8: c->longitude = atof(fieldBuffer); break;
            case 9: c->population = atoll(fieldBuffer);
        }

        /* Stop after reading the first nine fields */
        if (fieldNum >= 9) {
            break;
        }
    }
    return c;
}

/* Read cities from CSV file into an array */
int readCityList(char *filename, city *cities[], int n) {

    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printf("File does not exist!\n");
        return 0;
    }
    char buffer[20000];

    /* Remove header */
    fgets(buffer, 20000, f);

    int count = 0;
    while (count < n && fgets(buffer, 20000, f) != NULL) {
        killNewline(buffer);
        city *c = stringToCity(buffer);
        cities[count] = c;
        count++;
    }

    fclose(f);
    return count;
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

/* Solve the knapsack problem using dynamic programming */
void solveKnapsack(city *cities[], int cityCount, long long dp[][MAX_LENGTH + 1]) {

    /* Initialize DP table */
    for (int i = 0; i <= cityCount; i++) {
        for(int j = 0; j <= MAX_LENGTH; j++){
            dp[i][j] = 0;
        }
    }    

    /* Fill DP table */
    for(int i = 1; i <= cityCount; i++) {

        int length = cities[i-1]->length;
        long long population = cities[i-1]->population;

        for(int j = 0; j <= MAX_LENGTH; j++) {

            /* Do not select this city */
            dp[i][j] = dp[i-1][j];

            /* Select this city if it fits */
            if(length <= j) {

                long long choose = population + dp[i-1][j-length];

                if(choose > dp[i][j]) {
                    dp[i][j] = choose;
                }
            }
        }
    }
}

/* Backtracking to find and print all cities selected */
void backtracking(city *cities[], int cityCount, long long dp[][MAX_LENGTH + 1]) {
    int i = cityCount;
    int j = MAX_LENGTH;
    printf("Selected cities:\n");

    while (i > 0 && j > 0) { 
        /* city was selected */
        if (dp[i][j] != dp[i-1][j]) {
            printf("%s\n", cities[i - 1]->nameASCII);
            j -= cities[i - 1]->length;
        }
        i--;
    }
}

int main () {

    city *cities[MAX_CITIES];
    int numCities = MAX_CITIES;
    long long dp[MAX_CITIES + 1][MAX_LENGTH + 1];

    /* Read cities into array */
    int cityCount = readCityList("uscities.csv", cities, numCities);

    if (cityCount == 0) {
        return 1;
    }

    solveKnapsack(cities, cityCount, dp);

    /* Print population result and all cities selected */
    printf("The total population saved is %lld\n", dp[cityCount][MAX_LENGTH]);

    backtracking(cities, cityCount, dp);

    /* Free memory */
    for (int i = 0; i < cityCount; i++) {
        freeCity(cities[i]);
    }

    return 0;
}