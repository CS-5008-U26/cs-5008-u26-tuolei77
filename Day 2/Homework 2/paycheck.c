/* This program asks user for Hourly Rate and Number of Hours and calculate the total pay
 * For work more than 40 hours, the excess (over 40) is paid at 1.5 x the hourly rate.
 */

#include <stdio.h>

int main () {
    char s[100];
    double hourly_rate;
    double number_of_hours;
    double salary;
    double OVERPAY_RATE = 1.5;

    /* Using a loop to asks user for two more numbers after calculation */    
    while (1){

    /* Read a floating point number from the user */
    printf ("Enter an hourly rate: ");
    scanf("%lf", &hourly_rate);  
    fgets(s,100,stdin);

    /* If input is less than or equal to 0, exit the program */
    if (hourly_rate <= 0){
        break;
    }

    /* Read another floating point number from the user */
    printf ("Enter the number of hours worked: ");
    scanf("%lf", &number_of_hours);  
    fgets(s,100,stdin);

    /* If input is less than or equal to 0, exit the program */
    if (number_of_hours <= 0){
        break;
    }

    /* Calculate the pay using logic mentioned above */
    if (number_of_hours <= 40){
        salary = hourly_rate * number_of_hours;
    } else {
        salary = hourly_rate * 40 + hourly_rate * (number_of_hours - 40) * OVERPAY_RATE;
    }

    /* Display final result on the screen */
    printf ("You should be paid %.2f\n", salary);

    }
    fgets(s, 100, stdin);
    return 0;
}