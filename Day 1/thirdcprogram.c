#include <stdio.h>
int main() {

    char s[100];                            // define the string that the user will enter
    char a[100];                            // define the second string that the user will enter
    char t[100];                            // t is used to "pause" the console so it doesn't exit too quickly

    printf ("What is your name? ");         // prompt the user
    scanf("%s", s);                         // read a string from the console ("stdin")
    fgets(t,100,stdin);                     // sadly, we have to remove the \n that scanf leaves in stdin

    printf ("Which city do you live in? ");         // prompt the user
    scanf("%s", a);                         // read a string from the console ("stdin")
    fgets(t,100,stdin);                     // sadly, we have to remove the \n that scanf leaves in stdin

    printf("%s? That's a funny name!\n",s);   // tell the user what string they just entered
    printf("%s? That's a beautiful city!",a);   // tell the user what string they just entered

    /* Pause the console so we can look at it before it vanishes */
    fgets(t,100,stdin);
}