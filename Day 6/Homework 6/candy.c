/* This program reads candy data from candy-data.csv.
 * It prints all candy names, lists chocolate candies based on whether they have caramel
 * in different cases, and prints summary statistics.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Create a struct to store candy data */
typedef struct candy_struct {
    char *name;
    int chocolate;
    int fruity;
    int caramel;
    int peanutalmondy;
    int nougat;
    int crispedricewafer;
    int hard;
    int bar;
    int pluribus;
    double sugarpercent;
    double pricepercent;
    double winpercent;
} candy;

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

/* Convert one line of text into a candy struct */
candy *stringToCandy (char *textLine) {

    char fieldBuffer[1000];
    char *p = textLine;
    int fieldNum = 0;
    candy *c = malloc(sizeof(candy));

    while (p != NULL) {

        p = getNextField(p, ',', fieldBuffer);
        if (p == NULL) {
            break;
        }
        fieldNum++;
        switch (fieldNum) {
            case 1: c->name = strdup(fieldBuffer); break;
            case 2: c->chocolate = atoi(fieldBuffer); break;
            case 3: c->fruity = atoi(fieldBuffer); break;
            case 4: c->caramel = atoi(fieldBuffer); break;
            case 5: c->peanutalmondy = atoi(fieldBuffer); break;
            case 6: c->nougat = atoi(fieldBuffer); break;
            case 7: c->crispedricewafer = atoi(fieldBuffer); break;
            case 8: c->hard = atoi(fieldBuffer); break;
            case 9: c->bar = atoi(fieldBuffer); break;
            case 10: c->pluribus = atoi(fieldBuffer); break;
            case 11: c->sugarpercent = atof(fieldBuffer); break;
            case 12: c->pricepercent = atof(fieldBuffer); break;
            case 13: c->winpercent = atof(fieldBuffer); break;
        }
        if (fieldNum >= 13) {
            break;
        }
    }
    return c;
}

/* Count the number of candy data lines excluding the header */
int countLines(char *filename) {
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printf("No such file exist!\n");
        return 0;
    }

    char buffer[20000];
    int count = 0;

    /* Skip header */
    fgets(buffer, 20000, f);
    while (fgets(buffer, 20000, f) != NULL) {
        count++;
    }

    fclose(f);
    return count;
}

/* Read all candy data into an array of candy pointers */
candy** readCandyList (char *filename) {
    
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        printf("No such file exist!\n");
        return NULL;
    }

    char buffer[20000];
    int count;
    count = countLines(filename);

    candy **candyArray = malloc(count * sizeof(candy*));

    /* Skip header */
    fgets(buffer, 20000, f);
    for (int i = 0; i < count; i++) {
        fgets(buffer, 20000, f); 
        killNewline(buffer); 
        candyArray[i] = stringToCandy(buffer);
    }

    fclose(f);
    return candyArray;
}

/* Free one candy struct */
void freeCandy (candy *c) {
    free(c->name);
    free(c);
}

/* Print summary information for one attribute */
void printAttribute(candy **candyArray, int count, char *attrName, int *attrValues) {
    double totalSugar = 0;
    double totalPrice = 0;
    double totalWin = 0;
    int attrCount = 0;

    for (int i = 0; i < count; i++) {
        if (attrValues[i] == 1) {
            totalSugar += candyArray[i]->sugarpercent;
            totalPrice += candyArray[i]->pricepercent;
            totalWin += candyArray[i]->winpercent;
            attrCount++;
        }
    }

    printf("%s: avg sugar=%.2f%%, avg price=%.2f%%, avg win=%.2f%%\n", attrName,
    totalSugar / attrCount * 100, totalPrice / attrCount * 100, totalWin / attrCount);
}

/* Print summary for candies whose sugar percent is higher than average */
void printSugarHigher(candy **candyArray, int count) {
    double totalSugar = 0;
    double subsetSugar = 0;
    double subsetPrice = 0;
    double subsetWin = 0;
    double averageSugar;
    int subsetCount = 0;

    for (int i = 0; i < count; i++) {
        totalSugar += candyArray[i]->sugarpercent;
    }
    averageSugar = totalSugar / count;

    for (int i = 0; i < count; i++) {
        if (candyArray[i]->sugarpercent > averageSugar) {
            subsetSugar += candyArray[i]->sugarpercent;
            subsetPrice += candyArray[i]->pricepercent;
            subsetWin += candyArray[i]->winpercent;
            subsetCount++;
        }
    }

    printf("Above average sugar: avg sugar=%.2f%%, avg price=%.2f%%, avg win=%.2f%%\n",
    subsetSugar / subsetCount * 100, subsetPrice / subsetCount * 100, subsetWin / subsetCount);
}

/* Print summary for candies whose price percent is higher than average */
void printPriceHigher(candy **candyArray, int count) {
    double totalPrice = 0;
    double subsetSugar = 0;
    double subsetPrice = 0;
    double subsetWin = 0;
    double averagePrice;
    int subsetCount = 0;

    for (int i = 0; i < count; i++) {
        totalPrice += candyArray[i]->pricepercent;
    }
    averagePrice = totalPrice / count;

    for (int i = 0; i < count; i++) {
        if (candyArray[i]->pricepercent > averagePrice) {
            subsetSugar += candyArray[i]->sugarpercent;
            subsetPrice += candyArray[i]->pricepercent;
            subsetWin += candyArray[i]->winpercent;
            subsetCount++;
        }
    }

    printf("Above average price: avg sugar=%.2f%%, avg price=%.2f%%, avg win=%.2f%%\n",
        subsetSugar / subsetCount * 100, subsetPrice / subsetCount * 100, subsetWin / subsetCount);
}

/* Print all candy names */
void printAllCandies(candy **candyArray, int count) {
    printf("All candies:\n");

    for (int i = 0; i < count; i++) {
        printf("%s\n", candyArray[i]->name);
    }
}

/* Print chocolate candies and caramel percentage */
void printChocolateCandies(candy **candyArray, int count) {
    int chocolateCount = 0;
    int chocolateCaramelCount = 0;

    printf("\nChocolate candies:\n");

    for (int i = 0; i < count; i++) {
        if (candyArray[i]->chocolate == 1) {
            chocolateCount++;

            /* Print caramel candies in uppercase and non-caramel candies in lowercase */
            if (candyArray[i]->caramel == 1) {
                for (int j = 0; candyArray[i]->name[j] != '\0'; j++) {
                    printf("%c", toupper(candyArray[i]->name[j]));
                }
                printf("\n");
                chocolateCaramelCount++;
            } else {
                for (int j = 0; candyArray[i]->name[j] != '\0'; j++) {
                    printf("%c", tolower(candyArray[i]->name[j]));
                }
                printf("\n");
            }
        }
    }

    printf("Percent of chocolate candies with caramel: %.2f%%\n",
        (double) chocolateCaramelCount / chocolateCount * 100);
}

int main () {

    int count;
    count = countLines("candy-data.csv");
    
    if (count == 0) {
    return 1;
    }

    candy **candyArray = readCandyList("candy-data.csv");

    if (candyArray == NULL) {
        return 1;
    }

    int chocolate[count], fruity[count], caramel[count], peanutalmondy[count];
    int nougat[count], crispedricewafer[count], hard[count], bar[count], pluribus[count];

    /* Task 1 print the names of all the candies */
    printAllCandies(candyArray, count);

    /* Task 2 print all the chocolate and caramel candies of seletive information */
    printChocolateCandies(candyArray, count);

    /* Task 3 print summary information accordingly */
    printf("\nSummary by attribute:\n");

    /* Create int array for each attribute */
    for (int i = 0; i < count; i++) {
        chocolate[i] = candyArray[i]->chocolate;
        fruity[i] = candyArray[i]->fruity;
        caramel[i] = candyArray[i]->caramel;
        peanutalmondy[i] = candyArray[i]->peanutalmondy;
        nougat[i] = candyArray[i]->nougat;
        crispedricewafer[i] = candyArray[i]->crispedricewafer;
        hard[i] = candyArray[i]->hard;
        bar[i] = candyArray[i]->bar;
        pluribus[i] = candyArray[i]->pluribus;
    }

    printAttribute(candyArray, count, "chocolate", chocolate);
    printAttribute(candyArray, count, "fruity", fruity);
    printAttribute(candyArray, count, "caramel", caramel);
    printAttribute(candyArray, count, "peanutalmondy", peanutalmondy);
    printAttribute(candyArray, count, "nougat", nougat);
    printAttribute(candyArray, count, "crispedricewafer", crispedricewafer);
    printAttribute(candyArray, count, "hard", hard);
    printAttribute(candyArray, count, "bar", bar);
    printAttribute(candyArray, count, "pluribus", pluribus);

    printf("\n");
    printSugarHigher(candyArray, count);
    printPriceHigher(candyArray, count);

    for (int i = 0; i < count; i++) {
        freeCandy(candyArray[i]);
    }
    free(candyArray);

    return 0;
}