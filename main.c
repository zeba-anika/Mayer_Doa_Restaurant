//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Declarations
int tablestatus[10] = {0};
int order_id = 100;
int cart[5] = {0};
int total_price;

struct orderFormat {
    int status, orderid, tableno, burgerno, pizzano, sandwichno, cookiesno, colddrinksno, price;
} orderFormat;

struct orderFormat orderlist[10] = {0};

struct MenuType {
    char item_name[100];
    int item_price;
} MenuType;

struct MenuType Menu[5] = {{"Burger", 100}, {"Pizza", 80}, {"Sandwich", 60}, {"Cookies", 50}, {"Cold Drink", 30}};


void table();
void welcomescreen();
void customerwrite(int total_price, int cart[]);
void foodorder();

int main() {
    system("cls");
    while (1) {
        welcomescreen();
    }

    return 0;
}



void table() {
    int n;
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
    while(1){
        printf("Which table would you like to book?-");
        scanf("%d", &n);
        if(n==0){break;}

        tablestatus[n-1] = 1;
        printf("Table no %d has been reserved.\n\n", n);
    }

    system("cls");
}


void customerwrite(int total_price, int cart[]) {
    FILE *fptr;
    fptr = fopen("foodorder.txt", "a");
    if(fptr==NULL) return;
    fprintf(fptr, "%d 1 %d %d %d %d %d %d\n", order_id, cart[0], cart[1], cart[2], cart[3], cart[4], total_price);

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