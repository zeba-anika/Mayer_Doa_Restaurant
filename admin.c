#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function Declarations
void statusChanger();
void menu();
void sales(int x);


int main() {
    while (1) {
        menu();
    }
}


void sales(int x){
    int sum = 0, d;
    char line[100];
    char month_name[5];
    
    printf("Enter the first 3 characters of Month (i.e. Oct): ");
    scanf("%s", month_name);
    
    if (x == 3) {
        printf("Enter the Day (i.e. 21): ");
        scanf("%d", &d);
    }
    
    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];
        
        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula)) {

            // printf("%d\n", price);

            if (x == 2) {
                //For a month
                if (strcmp(month,month_name) == 0) {
                    sum += price;
                }
            }
            else if (x == 3) {
                //For a day
                if (strcmp(month,month_name) == 0 && date == d) {
                    sum += price;
                }
            }
        }
        
    }

    if (sum == 0) {
        system("cls");
        printf("No records found.\n\n");
    }
    else {
        system("cls");
        printf("Total monthly sales: %d BDT \n\n", sum);
    }
}


void statusChanger() {
    char arr[5];
    printf("Enter the OrderID ? ");
    scanf("%s", arr);
    char orders[1000];
    char line[100];
    char line2[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");
    while (fgets(line, 100, fptr)) {
        // printf("%s\n", line);
        strcpy(line2, line);
        char *ptr = strtok(line, " ");
        if (strcmp(arr, ptr) == 0) {
            if (line2[4] < '3') {
                system("cls");
                printf("Status Changed Successfully from %c to %c\n\n\n", line2[4], line2[4] + 1);
                line2[4]++;
            }
            else {
                system("cls");
                printf("Unable to change status. Current status is %c\n\n\n", line2[4]);
            }
        }
        strcat(orders, line2);
        
        
    }    
    fclose(fptr);
    
    fptr = fopen("foodorder.txt", "w");
    
    fprintf(fptr, "%s", orders);
    fclose(fptr);
}

void menu() {
    // system("cls");

    printf("------------------------\n");
    printf("|                      |\n");
    printf("|     Admin Panel      |\n");
    printf("|                      |\n");
    printf("------------------------\n");
    printf("Would you like to :\n");
    printf("\t1. Change Order Status.\n");
    printf("\t2. Get montly sales stats.\n");
    printf("\t3. Get daily sales stats.\n");

    int optionType;
    printf("Enter your option:");
    scanf("%d", &optionType);
    
    // system("cls");
    
    if(optionType==1){
        statusChanger();
    }
    else if(optionType==2 || optionType==3){
        sales(optionType);
    }
    else {
        system("cls");
        printf("Invalid option\n\n\n");
        return;
    }
}