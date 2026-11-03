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
void customerwrite(int total_price, int cart[]);
void foodorder();


//The main function
int main() {
    int role_choice;

    printf("====================================================\n");
    printf("       MAYER DOA RESTAURANT MANAGEMENT SYSTEM       \n");
    printf("====================================================\n\n");
    printf("Select your role to access your portal:\n\n");
    printf("  1. Customer Portal\n");
    printf("  2. Kitchen Portal\n");
    printf("  3. Audience Portal\n");
    printf("  4. Admin Portal\n");
    printf("  0. Exit System\n\n");
    printf("----------------------------------------------------\n");
    printf("Enter your choice (0-4): ");
    
    scanf("%d", &role_choice);

    switch (role_choice) {
        case 1:
            // Customer program launch korbe
            
            break;

        
        default:
            printf("\nInvalid choice! Please choose between 0-4.\n");
            break;
    }
    

    return 0;
}



//Function Declarations
void table() {
    int n;

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


void customerwrite(int total_price, int cart[]) {
    FILE *fptr;
    fptr = fopen("foodorder.txt", "a");
    if(fptr==NULL) return;
    
    //Checks current day
    char day_name[10], month_name[10];
    int day_num;
    time_t now = time(NULL);
    sscanf(ctime(&now), "%s %s %d", day_name, month_name, &day_num);

    fprintf(fptr, "%d 1 %d %d %d %d %d %d %d %s %d ", order_id, cart[0], cart[1], cart[2], cart[3], cart[4], total_price, day_num, month_name, table_counter);

    for (int i = 0; i < table_counter; i++) {
        fprintf(fptr, "%d,", current_table[i]);
    }
    
    fprintf(fptr, "\n");
    fclose(fptr);
}


void foodorder() {
    int item, count, cart[5] = {0}, total_price = 0;
    printf("<-- Menu -->\n");
    
    for (int i = 0; i < 5; i++) {
        printf("%d. %s - %d\n", i+1, Menu[i].item_name, Menu[i].item_price);
    }

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
            printf("Your Order ID: %d \n", ++order_id);
            printf("Your Total Bill: %d BDT\n\n\n", total_price);
            customerwrite(total_price, cart);
            break;
        }

        printf("How many %s? - ", Menu[item-1].item_name);
        scanf("%d", &count);

        if (item < 0 || count < 0) {
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
        foodorder();
    }
    else if(ordertype==2){
        foodorder();
    }
    else {
        printf("Invalid option\n");
        return;
    }
}