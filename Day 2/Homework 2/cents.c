/* This program accepts an integer number of cents from the user,
 * and prints the number of quarters, dimes, nickels, and pennies needed.
 */

#include <stdio.h>

/* A helper function that helps decide the output */
void print_coin(int count, char singular[], char plural[]) {
    if (count == 1) {
        printf("%d %s", count, singular);
    } else {
        printf("%d %s", count, plural);
    }
}

int main () {
    char s[100];
    int cents;
    int quarters, dimes, nickels, pennies;
    int remainder;

    /* Read an integer from the user */
    while(1) {
    printf ("Enter a number of cents: ");
    scanf("%d", &cents);  
    fgets(s,100,stdin);

    /* Use loop to ensure input is between 1 and 100 */
    if (cents < 1 || cents > 100){
        printf ("Your input is invalid. Please enter a number between 1 and 100.\n");
    } else{
        break;
    }
    }

    /* Calculate the number of coins needed */
    quarters = cents / 25;
    remainder = cents % 25;
    dimes = remainder / 10;
    remainder %= 10;
    nickels = remainder / 5;
    remainder %= 5;
    pennies = remainder;

    /* Display final result on the screen */
    printf ("That requires ");

    /* Display number of quarters and corresponding punctuations. */
    if (quarters != 0){
        print_coin(quarters, "quarter", "quarters");
        if (dimes == 0 && nickels == 0 && pennies == 0){
            printf(".\n");
        } else {
            printf(", ");
        }
    }

    /* Display number of dimes and corresponding punctuations. */
    if (dimes != 0){
        if (quarters != 0 && nickels == 0 && pennies == 0) {
            printf("and ");
        } 
        print_coin(dimes, "dime", "dimes");
        if (nickels == 0 && pennies == 0){
            printf(".\n");
        } else {
            printf(", ");
        }
    }

    /* Display number of nickels and corresponding punctuations. */
    if (nickels != 0){
        if ((quarters != 0 || dimes != 0) && pennies == 0) {
            printf("and ");
        } 
        print_coin(nickels, "nickel", "nickels");
        if (pennies == 0){
            printf(".\n");
        } else {
            printf(", ");
        }
    }

    /* Display number of pennies and corresponding punctuations. */
    if (pennies != 0){
        if (quarters != 0 || dimes != 0 || nickels != 0){
            printf("and ");
        }
        print_coin(pennies, "penny", "pennies");
        printf(".\n");
    }

    fgets(s, 100, stdin);
    return 0;
}

