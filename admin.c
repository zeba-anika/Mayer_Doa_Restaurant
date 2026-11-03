#include <stdio.h>
#include <string.h>

//Function Declarations
void seatreleaser();
void statusChanger();
void menu();
void sales();
int main() {
    menu();

    return 0;
}
void sales(){
    int sum = 0;
    char line[100];
    char month_name[5];
    printf("Enter the first 3 characters of Month: ");
    scanf("%s",month_name);

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];
        
        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula));

        // printf("%d\n", price);
        if (strcmp(month,month_name) == 0) {
            sum += price;
        }
        else {
            printf("No records found for the month.\n");
            break;
        }
    }

    printf("Total monthly sales: %d BDT", sum);
    
}

void seatreleaser() {
    
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
        if (strcmp(arr, ptr) == 0)
            line2[4]++;

        strcat(orders, line2);
        
        
    }    
    fclose(fptr);
    
    fptr = fopen("foodorder.txt", "w");
    
    fprintf(fptr, "%s", orders);
    fclose(fptr);
}

void menu() {
    printf("------------------------\n");
    printf("|                      |\n");
    printf("|     Admin Panel      |\n");
    printf("|                      |\n");
    printf("------------------------\n");
    printf("Would you like to :\n");
    printf("\t1. Change Order Status.\n");
    printf("\t2. Get montly sales stats.\n");

    int optionType;
    printf("Enter your option:");
    scanf("%d", &optionType);
    
    // system("cls");
    
    if(optionType==1){
        statusChanger();
    }
    else if(optionType==2){
        sales();
    }
    else {
        printf("Invalid option\n");
        return;
    }
}