//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Global Declarations
int tablestatus[10] = {0};
int order_id = 100;
int cart[5] = {0};
int total_price;
int table_counter = 0;
int current_table[10] = {0};

struct MenuType {
    char item_name[100];
    int item_price;
} MenuType;

struct MenuType Menu[5] = {{"Burger", 100}, {"Pizza", 80}, {"Sandwich", 60}, {"Cookies", 50}, {"Cold Drink", 30}};


void table();
void welcomescreen();
void customerwrite(int total_price, int cart[], int z);
void foodorder(int z);

int main() {
    system("cls");
    while (1) {
        welcomescreen();
    }
}



void table() {
    int n;

    for (int i = 0; i < 10; i++) {
        tablestatus[i] = 0;
    }

    char line[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];
        
        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula)) {
            // puts(tablegula);

            //Returns First Token
            char *ptr = strtok(tablegula, ",");
            
            //Keeps printing further tokens
            
            while (ptr != NULL){
                if ((status == 1 || status == 2) && (atoi(ptr) != 0)) {
                    tablestatus[atoi(ptr) - 1] = 1;
                }
                else if ((status == 3) && (atoi(ptr) != 0)) {
                    tablestatus[atoi(ptr) - 1] = 0;
                }

                // printf("Seat no %d status is %d\n", atoi(ptr), tablestatus[atoi(ptr) - 1]);
                
                ptr = strtok(NULL, ",");
            }
        }
    }


    fclose(fptr);

    for (int i = 0; i < 10; i++) {
        current_table[i] = 0;
    }

    

    printf("----Table Booking System----\n");
    for (int i = 0; i < 10; i++){
        if (tablestatus[i]==0) {
            printf("Table %d is Free. \n", i + 1);
        }
        else{
            printf("Table %d is Booked. \n", i + 1);
        }
    }
    printf("\nEnter 0 to exit\n");
    table_counter = 0;



    while(1){
        printf("Which table would you like to book?-");
        scanf("%d", &n);
        if(n==0){break;}

        for (int i = 0; i < 10; i++) {
            if (tablestatus[n-1] == 1) {
                printf("This table is already reserved. Try another one.\n");
                break;
            }
        }

        
        if (tablestatus[n-1] == 0) {
            current_table[table_counter] = n;
            table_counter++;
            tablestatus[n-1] = 1;
            printf("Table no %d has been reserved.\n\n", n);
        }
    }

    
    system("cls");
    printf("You have reserved seat no: ");
    
    for (int i = 0; i < table_counter; i++) {
        printf("%d ", current_table[i]);
    }
    printf("\n");
}


void customerwrite(int total_price, int cart[], int z) {
    FILE *fptr;
    fptr = fopen("foodorder.txt", "a");
    if(fptr==NULL) return;
    
    int real_status = 0;
    
    for (int i = 0; i < 5; i++) {
        if (cart[i] != 0) {
            real_status = 1;
        }
    }

    if (real_status == 0) {
        return;
    }

    //Checks current day
    char day_name[10], month_name[10];
    int day_num;
    time_t now = time(NULL);
    sscanf(ctime(&now), "%s %s %d", day_name, month_name, &day_num);

    if (z == 2) {
        table_counter = 0;
    }

    fprintf(fptr, "%d 1 %d %d %d %d %d %d %d %s %d ", order_id, cart[0], cart[1], cart[2], cart[3], cart[4], total_price, day_num, month_name, table_counter);

    if (z == 1) {
        for (int i = 0; i < table_counter; i++) {
            fprintf(fptr, "%d,", current_table[i]);
        }
    }
    else if (z == 2) {
        fprintf(fptr, "%d,", 0);
    }

    
    fprintf(fptr, "\n");
    fclose(fptr);
}


void foodorder(int z) {
    int item, count, cart[5] = {0}, total_price = 0;
    printf("\n <-- Menu -->\n\n");
    
    int invalid_food_no = 0, invalid_food_items[5] = {0};
    char line[100] = {0};
        
    FILE *fptr;
    fptr = fopen("foodstock.txt", "r");

    int klm_counter = 0;
    while (fgets(line, 100, fptr)) {
        int food_item_no, food_status;
        char food_name[20];
        
        if (sscanf(line, "%d %d %s", &food_item_no, &food_status, food_name)) {
            if (food_status) {
                printf("%d. %s - %d BDT\n", klm_counter+1, Menu[klm_counter].item_name, Menu[klm_counter].item_price);
                printf("\n");
            } 
            else {
                invalid_food_items[invalid_food_no] = food_item_no;
                invalid_food_no++;
            } 
            klm_counter++;              
        }
    }

    fclose(fptr);

    printf("Type 0 to exit.\n");
    while (1) {
        printf("Which item do you want?- ");
        scanf("%d", &item);
        if (item == 0) {
            system("cls");
            printf("Your Order has been placed successfully\n\n");
            printf("---- Your Receipt ---- \n\n");
            for (int i = 0; i < 5; i++) {
                if (cart[i] != 0) {
                    total_price += cart[i]*Menu[i].item_price;
                    printf("You have selected %d %s(s)\n", cart[i], Menu[i].item_name);
                }
            }

            int real_status = 0;
    
            for (int i = 0; i < 5; i++) {
                if (cart[i] != 0) {
                    real_status = 1;
                }
            }

            if (real_status) {
                printf("Your Order ID: %d \n", ++order_id);
                printf("Your Total Bill: %d BDT\n\n\n", total_price);
                customerwrite(total_price, cart, z);
                break;
            }
            else {
                printf("You haven't ordered anything!\n");
                break;
            }

        }

        if (item < 0 || item > 5 || invalid_food_items[0] == item ||  invalid_food_items[1] == item || invalid_food_items[2] == item || invalid_food_items[3] == item || invalid_food_items[4] == item) {
            printf("Your given option is invalid\n");
            count = 0;
        }
        else {
            printf("How many %s? - ", Menu[item-1].item_name);
            scanf("%d", &count);
        }

        if (count < 0) {
            printf("Your given option is invalid\n");
        }
        else {
            cart[item - 1] = count;
        }
    }

    printf("\n\n\nPlease, Enter 0 to clear the screen.\n");
    int zero = 1;
    scanf("%d", &zero);
    if (zero == 0) {
        system("cls");
    }
}


void welcomescreen() {
    printf("------------------------\n");
    printf("|                      |\n");
    printf("| Mayer Doa Restaurant |\n");
    printf("|                      |\n");
    printf("------------------------\n");
    printf("Would you like to :\n");
    printf("\t1.Dine in.\n");
    printf("\t2.Takeaway.\n");

    int ordertype;
    printf("Enter your option:");
    scanf("%d", &ordertype);
    
    system("cls");
    
    if(ordertype==1){
        table();
        foodorder(1);
    }
    else if(ordertype==2){
        foodorder(2);
    }
    else {
        printf("Invalid option\n");
        return;
    }
}