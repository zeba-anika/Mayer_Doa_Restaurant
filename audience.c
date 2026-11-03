#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Update_AS();

int main() {
    for (;;) {
        Update_AS();

        fflush(stdout); 
        sleep(3); 
    }
}

void Update_AS() {

    system("cls");

    printf(" ----- Welcome to Diners Screen ----- \n\n\n");

    char line[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich ,cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];
        
        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula)) {
            if (status == 2) {
                printf("OrderID %d || Your Food is Ready || For Table: ", id);
                puts(tablegula);
                printf("\n");
            }
        }
    }

    fclose(fptr);
}