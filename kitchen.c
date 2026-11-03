// Imports libraries for the program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function Declarations
void Update_KS();

int main() {
    for (;;) {
        // Loads the chef's screen
        Update_KS();

        // Clears the screen and waits for 3 seconds before updating the chef's screen again
        fflush(stdout);
        sleep(3);
    }
}

// Function to update the chef's screen with the current orders
void Update_KS() {
    system("cls");
    printf(" ----- Welcome to Chef's Screen ----- \n\n\n");

    char line[100];

    // Reads the current orders from the DB File and displays them on the chef's screen
    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];

        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula)) {
            if (status == 1) {
                printf("OrderID %d || %d Burgers, %d Pizzas, %d Sandwiches, %d Cookies, %d ColdDrinks || For Table: ", id, status, burger, pizza, sandwich, cookies, coldDrinks);
                puts(tablegula);
                printf("\n");
            }
        }
    }

    fclose(fptr);
}