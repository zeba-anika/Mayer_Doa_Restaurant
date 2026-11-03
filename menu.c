#include <stdio.h>
#include <stdlib.h>

int main() {
    int role_choice;

    printf("====================================================\n");
    printf("       MAYER DOA RESTAURANT MANAGEMENT SYSTEM       \n");
    printf("====================================================\n\n");
    printf("Select your role to access your portal:\n\n");
    printf("  1. Customer Portal   (Order Food & Track Status)\n");
    printf("  2. Chef Portal       (Kitchen Display & Food Status)\n");
    printf("  3. Manager / Cashier (Sales Report & Analytics)\n");
    printf("  4. Exit System\n\n");
    printf("----------------------------------------------------\n");
    printf("Enter your choice (1-4): ");

    scanf("%d", &role_choice);

    switch (role_choice) {
    case 1:
        system("cls");
        // Customer program launch korbe
        system("customer.exe");
        break;

    default:
        printf("\nInvalid choice! Please choose between 1 and 4.\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
        break;
    }

    return 0;
}