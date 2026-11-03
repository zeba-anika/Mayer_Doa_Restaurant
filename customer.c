// Imports libraries for the program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Defining colors
#define COLOR_RESET       "\033[0m"
#define COLOR_DEEP_BLUE   "\033[1;34m"
#define COLOR_LIGHT_BLUE  "\033[1;36m"
#define COLOR_BRIGHT_WHITE  "\033[38;2;255;255;255m"

// Global variables for the program
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

// Function Declarations
void table();
void welcomescreen();
void customerwrite(int total_price, int cart[], int z);
void foodorder(int z);

int main() {
    system("cls");

    // Records last orderID to keep going where we left off
    char line[100] = {0};

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        sscanf(line, "%d", &order_id);
    }

    fclose(fptr);

    // Keeps running the customer screen
    while (1) {
        welcomescreen();
    }
}

// Display the table booking and Handle reservations
void table() {
    int n;

    for (int i = 0; i < 10; i++) {
        tablestatus[i] = 0;
    }

    // Checks table status before continuing
    char line[100];

    FILE *fptr;
    fptr = fopen("foodorder.txt", "r");

    while (fgets(line, 100, fptr)) {
        int id, status, burger, pizza, sandwich, cookies, coldDrinks, price, date, table_num;

        char month[5];
        char tablegula[25];

        if (sscanf(line, "%d %d %d %d %d %d %d %d %d %s %d %s", &id, &status, &burger, &pizza, &sandwich, &cookies, &coldDrinks, &price, &date, month, &table_num, tablegula)){
            char *ptr = strtok(tablegula, ",");

            while (ptr != NULL) {
                if ((status == 1 || status == 2) && (atoi(ptr) != 0)) {
                    tablestatus[atoi(ptr) - 1] = 1;
                }
                else if ((status == 3) && (atoi(ptr) != 0)) {
                    tablestatus[atoi(ptr) - 1] = 0;
                }

                ptr = strtok(NULL, ",");
            }
        }
    }

    fclose(fptr);

    for (int i = 0; i < 10; i++) {
        current_table[i] = 0;
    }

    // Display table status
    printf(COLOR_BRIGHT_WHITE"-----------------  Table Booking System  ----------------\n"COLOR_RESET);
    
    int free_table_flag = 0;
    for (int i = 0; i < 10; i++) {
        if (tablestatus[i] == 0) {
            free_table_flag = 1;
            break;
        }
    }


    printf("\n");
    printf("_________________________________________________________\n\n");
    for (int i = 0; i < 10; i++) {
        if (tablestatus[i] == 1) {
            printf(" [  ------  ]   ");
        }
        else {        
            if (i == 9) {
                printf(COLOR_LIGHT_BLUE" [ Table %d ]   "COLOR_RESET, i + 1);
            }
            else {
                printf(COLOR_LIGHT_BLUE" [ Table 0%d ]   "COLOR_RESET, i + 1);
            }
        }
        
        
        if (i == 0 || i == 3 || i == 6) {
            printf("        ");
        }
        
        if ((i+1)%3 == 0) {
            printf("\n\n\n\n");
        }
    }
    printf(COLOR_DEEP_BLUE"         [ ----- Payment Desk ----- ]"COLOR_RESET);
    printf("\n\n");
    printf("_________________________________________________________\n");
    


    
    if (free_table_flag == 0) {
        printf("\nNo tables are Available. Takeaway at your service.\n");
    }

    printf("\nEnter 0 to exit\n");
    table_counter = 0;

    // Book a table
    while (1) {
        printf("Which table would you like to book?-");
        scanf("%d", &n);
        if (n == 0) {
            break;
        }
        else if(n < 0 || n > 10) {
            printf("Invalid Option.\n");           
        }
        else {
            for (int i = 0; i < 10; i++) {
                if (tablestatus[n - 1] == 1) {
                    printf("This table is already reserved. Try another one.\n");
                    break;
                }
            }

            if (tablestatus[n - 1] == 0) {
                current_table[table_counter] = n;
                table_counter++;
                tablestatus[n - 1] = 1;
                printf("Table no %d has been reserved.\n\n", n);
            }
        }
    }

    system("cls");
    printf("\nYou have reserved seat no: ");

    for (int i = 0; i < table_counter; i++) {
        printf("%d ", current_table[i]);
    }
    printf("\n");
}

// Write the full customer's order to the history log
void customerwrite(int total_price, int cart[], int z) {
    FILE *fptr;
    fptr = fopen("foodorder.txt", "a");
    if (fptr == NULL)
        return;

    int real_status = 0;

    // Checks if the customer has ordered anything
    for (int i = 0; i < 5; i++) {
        if (cart[i] != 0) {
            real_status = 1;
        }
    }

    if (real_status == 0) {
        return;
    }

    // Check current date
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

// Show menu and food order
void foodorder(int z) {
    int item, count, cart[5] = {0}, total_price = 0;
    printf("\n" COLOR_BRIGHT_WHITE"---------  Food Menu  ---------"COLOR_RESET"\n\n");

    int invalid_food_no = 0, invalid_food_items[5] = {0};
    char line[100] = {0};

    // Food item availability check
    FILE *fptr;
    fptr = fopen("foodstock.txt", "r");

    int klm_counter = 0;
    while (fgets(line, 100, fptr)) {
        int food_item_no, food_status;
        char food_name[20];

        if (sscanf(line, "%d %d %s", &food_item_no, &food_status, food_name)) {
            if (food_status) {
                printf("%d. %s\t-    "COLOR_LIGHT_BLUE"%d BDT"COLOR_RESET"\n", klm_counter + 1, Menu[klm_counter].item_name, Menu[klm_counter].item_price);
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

    // Order food items
    while (1) {
        printf("\nWhich item do you want?- ");
        scanf("%d", &item);
        if (item == 0) {
            system("cls");
            printf("Your Order has been placed successfully\n\n");
            printf(COLOR_BRIGHT_WHITE"---- Your Receipt ---- \n\n"COLOR_RESET);
            for (int i = 0; i < 5; i++) {
                if (cart[i] != 0) {
                    total_price += cart[i] * Menu[i].item_price;
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
                printf("\nYour Order ID: %d \n", ++order_id);
                printf("Your Total Bill: %d BDT\n\n\n", total_price);
                customerwrite(total_price, cart, z);
                break;
            }
            else {
                printf("You haven't ordered anything!\n");
                break;
            }
        }

        if (item < 0 || item > 5 || invalid_food_items[0] == item || invalid_food_items[1] == item || invalid_food_items[2] == item || invalid_food_items[3] == item || invalid_food_items[4] == item) {
            printf("Your given option is invalid\n");
            count = 0;
        }
        else {
            printf("How many %s? - ", Menu[item - 1].item_name);
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

// Welcome screen and ask the choice between dine-in and takeaway
void welcomescreen() {
    printf("------------------------\n");
    printf("|                      |\n");
    printf("| "COLOR_BRIGHT_WHITE"Mayer Doa Restaurant"COLOR_RESET" |\n");
    printf("|                      |\n");
    printf("------------------------\n");
    printf("\nWould you like to :\n");
    printf("   1. Dine in.\n");
    printf("   2. Takeaway.\n");

    int ordertype;
    printf("\nEnter your option:");
    scanf("%d", &ordertype);

    system("cls");

    if (ordertype == 1) {
        // Loads table reservation and food order
        table();
        foodorder(1);
    }
    else if (ordertype == 2) {
        // Loads food order
        foodorder(2);
    }
    else {
        printf("Invalid option\n");
        return;
    }
}