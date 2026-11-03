#include <stdio.h>

int main() {
    char line[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        if (line[4] == '1') {
            printf("%c%c%c: %c Burgers, %c Pizzas, %c Sandwiches, %c Cookies, %c ColdDrinks\n", line[0], line[1], line[2],  line[6], line[8], line[10], line[12], line[14]);
        }
    }

    fclose(fptr);
}