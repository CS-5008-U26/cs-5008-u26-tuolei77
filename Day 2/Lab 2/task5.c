#include <stdio.h>

int main () {
    char s[100];
    double price = -1;
    double TAX = 0.08;
    

    while (1){
        printf ("Enter a price in dollars:  ");
        scanf("%lf", &price);  
        fgets(s,100,stdin);

        if (price == 0){
            break;
        }

        double price_final = price * (1 + TAX);  // add 8% tax
        printf("The value with tax is $%.2f\n", price_final);
    }

    fgets(s, 100, stdin);
    return 0;
}