#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void print_header(const char *title) {
    int i;
    int width     = 42;
    int title_len = strlen(title);
    int padding   = (width - title_len) / 2;

    printf("\n");
    for (i = 0; i < width; i++) printf("=");
    printf("\n");

    for (i = 0; i < padding; i++) printf(" ");
    printf("%s\n", title);

    for (i = 0; i < width; i++) printf("=");
    printf("\n");
}

void show_menu() {
    clear_screen();
    printf("\n==========================================\n");
    printf("          ATM SIMULATOR MENU\n");
    printf("==========================================\n");
    printf("  1. Create New Account\n");
    printf("  2. Login\n");
    printf("  ------ (Login Required) ------\n");
    printf("  3. Check Balance\n");
    printf("  4. Withdraw Money\n");
    printf("  5. Deposit Money\n");
    printf("  6. View Transactions\n");
    printf("  7. Logout\n");
    printf("  ----------------------------------\n");
    printf("  8. Exit\n");
    printf("==========================================\n");
}

void print_not_logged_in_error() {
    printf("\n  Access Denied!\n");
    printf("  Please login first (Option 2).\n");
}