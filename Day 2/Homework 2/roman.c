/* This program asks the user for an integer between 1 and 4000
 * and prints the corresponding Roman numeral.
 */

#include <stdio.h>
#include <string.h>

int main () {
    char s[100];
    int x;
    int thousands, hundreds, tens, units;
   
    /* Read an integer from the user */
    printf ("Enter a number between 1 and 4000: ");
    scanf("%d", &x);  
    fgets(s,100,stdin);

    /* Print Roman numeral or an error message if input is out of bound. */
    if (x < 1 || x > 4000) {
        printf ("Your input is invalid. Please enter a number between 1 and 4000.\n");
    } else {
        /* Calculate the thousands, hundreds, tens and units number. */
        thousands = x / 1000;
        x %= 1000;
        hundreds = x / 100;
        x %= 100;
        tens = x / 10;
        x %= 10;
        units = x;

        /* Display message based on number given. */
        printf("The Roman Numeral: ");
        
        /* Display thousands in Roman numerals. */
        switch (thousands)
        {
        case 1:
            printf ("M");
            break;
        case 2:
            printf ("MM");
            break;
        case 3:
            printf ("MMM");
            break;  
        case 4:
            printf("MMMM");
            break;      
        default:
            break;
        }

        /* Display hundreds in Roman numerals. */
        switch (hundreds)
        {
        case 1:
            printf ("C");
            break;
        case 2:
            printf ("CC");
            break;
        case 3:
            printf ("CCC");
            break;        
        case 4:
            printf ("CD");
            break;        
        case 5:
            printf ("D");
            break;
        case 6:
            printf ("DC");
            break;
        case 7:
            printf ("DCC");
            break;        
        case 8:
            printf ("DCCC");
            break;        
        case 9:
            printf ("CM");
            break;                     
        default:
            break;
        }

        /* Display tens in Roman numerals. */
        switch (tens)
        {
        case 1:
            printf ("X");
            break;
        case 2:
            printf ("XX");
            break;
        case 3:
            printf ("XXX");
            break;        
        case 4:
            printf ("XL");
            break;        
        case 5:
            printf ("L");
            break;
        case 6:
            printf ("LX");
            break;
        case 7:
            printf ("LXX");
            break;        
        case 8:
            printf ("LXXX");
            break;        
        case 9:
            printf ("XC");
            break;                     
        default:
            break;
        }
    
        /* Display units in Roman numerals. */
        switch (units)
        {
        case 1:
            printf ("I");
            break;
        case 2:
            printf ("II");
            break;
        case 3:
            printf ("III");
            break;        
        case 4:
            printf ("IV");
            break;        
        case 5:
            printf ("V");
            break;
        case 6:
            printf ("VI");
            break;
        case 7:
            printf ("VII");
            break;        
        case 8:
            printf ("VIII");
            break;        
        case 9:
            printf ("IX");
            break;                     
        default:
            break;
        }
    }

    printf ("\n");

    fgets(s,100,stdin);
    return 0;
}