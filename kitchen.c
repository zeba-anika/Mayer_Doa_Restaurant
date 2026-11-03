#include <stdio.h>

int main() {
    char line[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];
        
        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula)) {
            if (status == 1) {
                printf("OrderID %d || %d Burgers, %d Pizzas, %d Sandwiches, %d Cookies, %d ColdDrinks || For Table: ", id, status, burger, pizza, sandwich ,cookies, coldDrinks);
                puts(tablegula);
                printf("\n");
            }
        }
    }

    fclose(fptr);
    return 0;
}