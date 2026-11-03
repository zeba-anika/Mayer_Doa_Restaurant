#include <stdio.h>
#include <string.h>

int main() {
    char orders[1000];
    char arr[5];
    printf("Which orderID is ready to be served? ");
    gets(arr);
    char line[100];
    char line2[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");
    while (fgets(line, 100, fptr)) {
        printf("%s\n", line);
        strcpy(line2, line);
        char *ptr = strtok(line, " ");
        if (strcmp(arr, ptr) == 0)
            line2[4] = '2';

        strcat(orders, line2);
        
        
    }
    // printf("\n\n Below is the new array\n\n");
    // puts(orders);
    
    fclose(fptr);
    
    fptr = fopen("foodorder.txt", "w");
    
    fprintf(fptr, "%s", orders);
    fclose(fptr);
}