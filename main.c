
#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#include "auth.h"
#include "transaction.h"
#include "filehandler.h"
#include "ui.h"

static void handle_choice(int choice, int *logged_in) {
    switch (choice) {

        
        case 1:
            create_account();
            break;

        
        case 2:
            if (*logged_in) {
                printf("\n  You are already logged in as %s!\n",
                       current_user->name);
                printf("  Please logout first.\n");
            } else {
                *logged_in = login();
            }
            break;

        
        case 3:
            if (*logged_in) {
                check_balance();
            } else {
                print_not_logged_in_error();
            }
            break;

        
        case 4:
            if (*logged_in) {
                withdraw();
            } else {
                print_not_logged_in_error();
            }
            break;

        
        case 5:
            if (*logged_in) {
                deposit();
            } else {
                print_not_logged_in_error();
            }
            break;

        
        case 6:
            if (*logged_in) {
                view_transactions();
            } else {
                print_not_logged_in_error();
            }
            break;

        
        case 7:
            logout(logged_in);
            break;

        
        case 8:
            printf("\n  Thank you for using ATM Simulator!\n");
            printf("  Goodbye!\n\n");
            exit(0);

        
        default:
            printf("\n  ✗ Invalid choice!\n");
            printf("  Please enter a number from 1 to 8.\n");
    }
}

static void wait_for_enter() {
    printf("\n  Press Enter to continue...");
    getchar();
}

int main() {
    int choice;
    int logged_in = 0;  

    
    clear_screen();
    printf("\n==========================================\n");
    printf("      WELCOME TO ATM SIMULATOR\n");
    printf("==========================================\n\n");

    
    load_accounts();

    
    while (1) {

        
        show_menu();

        
        printf("\n  Enter your choice (1-8): ");
        scanf("%d", &choice);
        getchar();  

        
        handle_choice(choice, &logged_in);

        
        wait_for_enter();
    }

    return 0; 
}