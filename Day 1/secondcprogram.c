#include <stdio.h>
int main() {

    char s[100];                            // define the string that the user will enter
    char t[100];                            // t is used to "pause" the console so it doesn't exit too quickly

    printf ("What is your name? ");         // prompt the user
    scanf("%s", s);                         // read a string from the console ("stdin")
    fgets(t,100,stdin);                     // sadly, we have to remove the \n that scanf leaves in stdin
    printf("%s? That's a funny name!",s);   // tell the user what string they just entered

    /*
    Changes made:
    1. Add comments to the program
    2. Change first fgets(s,100,stdin) to fgets(t,100,stdin) because we don't want to overwrite user input
    3. Change line 10 t to s because we want to print the string got from the user
    4. Add one more fgets(t,100,stdin) at the end to pause the console
    */

    /* Pause the console so we can look at it before it vanishes */
    fgets(t,100,stdin);
}
