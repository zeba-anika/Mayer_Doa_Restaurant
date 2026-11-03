// Imports libraries for the program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function Declarations
void Update_AS();

int main() {
    for (;;) {
        // Loads the diner's screen
        Update_AS();

        // Clears the screen and waits for 3 seconds before updating the diner's screen again
        fflush(stdout);
        sleep(3);
    }
}

// Function to update the diner's screen with the current orders
void Update_AS() {
    system("cls");
    printf(" ----- Welcome to Diners Screen ----- \n\n\n");

    char line[100];

    // Reads the current orders from the DB File and displays them on the diner's screen
    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

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