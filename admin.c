#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function Declarations
void statusChanger();
void menu();
void sales(int x);
void FoodStatus(int y);
void new_session_seat_releaser();
void new_session_with_food_restock();


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

void FoodStatus(int y) {
    char line[100] = {0};
    char line2[100] = {0};
    char orders[1000] = {0};
    
    FILE *fptr;
    fptr = fopen("foodstock.txt", "r");

    while (fgets(line, 100, fptr)) {
        strcpy(line2, line);
        
        int food_item_no, food_status;
        char food_name[20];
        
        if (sscanf(line, "%d %d %s", &food_item_no, &food_status, food_name)) {
            if(y == food_item_no) {
                if (food_status == 1) line2[2] = '0';
                else if (food_status == 0) line2[2] = '1';
            }
        
            strcat(orders, line2);
        }
    }

    fclose(fptr);
    
    fptr = fopen("foodstock.txt", "w");
    fprintf(fptr, orders);
    
    fclose(fptr);
}


void new_session_with_food_restock() {
    char line[100] = {0};
    char orders[1000] = {0};
    
    FILE *fptr;
    fptr = fopen("foodstock.txt", "r");
    while (fgets(line, 100, fptr)) {       
        line[2] = '1';
        strcat(orders, line);
    }

    fclose(fptr);
    
    fptr = fopen("foodstock.txt", "w");
    fprintf(fptr, orders);
    fclose(fptr);

    printf("All food items have been restocked.\n\n");
}



void statusChanger() {
    char arr[5];
    printf("Enter the OrderID ? ");
    scanf("%s", arr);
    char orders[1000] = {0};
    char line[100] = {0};
    char line2[100] = {0};

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

void new_session_seat_releaser() {
    char orders[1000] = {0};
    char line[100] = {0};
    char line2[100] = {0};

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");
    while (fgets(line, 100, fptr)) {
        strcpy(line2, line);
        line2[4] = '3';
        strcat(orders, line2);
    }    
    fclose(fptr);
    
    fptr = fopen("foodorder.txt", "w");
    fprintf(fptr, "%s", orders);
    fclose(fptr);

    system("cls");
    printf("New session has been started.\nAll tables have been released.\n");
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
    printf("\t4. Update Food Availability Status.\n");
    printf("\t5. Start New Session.\n");
    printf("\t6. Start New Session and Restock all Food Items.\n");

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
    else if(optionType==4){
        system("cls");
        int y;
        char line[100] = {0};
        
        FILE *fptr;
        fptr = fopen("foodstock.txt", "r");

        while (fgets(line, 100, fptr)) {
            int food_item_no, food_status;
            char food_name[20];
            
            if (sscanf(line, "%d %d %s", &food_item_no, &food_status, food_name)) {
                printf("%d. %s is ", food_item_no, food_name);
                if (food_status)
                    printf("available.\n");
                else
                    printf("not available.\n");
            }
            printf("\n");
        }
        

        fclose(fptr);

        
        
        printf("Enter 0 to exit\n");
        printf("Which item's availability would you like to change? (0-5): \n\n");
        scanf("%d", &y);

        if (y > 0 && y < 6) {
            FoodStatus(y);
            system("cls");
            printf("Status changed Successfully\n\n");
        }
        else if(y == 0) {
            system("cls");
            return;
        }
        else {
            system("cls");
            printf("Invalid option\n\n\n");
            return;
        }
    }
    else if(optionType==5){
        system("cls");
        new_session_seat_releaser();
        return;
    }
    else if(optionType==6){
        system("cls");
        new_session_seat_releaser();
        new_session_with_food_restock();
        return;
    }
    else {
        system("cls");
        printf("Invalid option\n\n\n");
        return;
    }
}