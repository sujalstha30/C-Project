#include <stdio.h>
#include "auth.h"
#include "account.h"
#include "ui.h"

static int get_account_number() {
    int acc_num;
    printf("  Enter Account Number: ");
    scanf("%d", &acc_num);
    getchar();
    return acc_num;
}

int verify_pin(int account_index) {
    int pin;
    int attempts = 0;

    while (attempts < MAX_LOGIN_ATTEMPTS) {
        printf("  Enter PIN: ");
        scanf("%d", &pin);
        getchar();

        if (accounts[account_index].pin == pin) {
            return 1;
        }

        attempts++;
        int remaining = MAX_LOGIN_ATTEMPTS - attempts;

        if (remaining > 0) {
            printf("\n  Wrong PIN! %d attempt(s) remaining.\n\n", remaining);
        }
    }

    printf("\n  Too many wrong attempts!\n");
    printf("  Please contact the bank.\n");
    return 0;
}

int login() {
    int acc_num;
    int account_index;

    print_header("LOGIN");

    acc_num       = get_account_number();
    account_index = find_account(acc_num);

    if (account_index == -1) {
        printf("\n  Account number %d not found!\n", acc_num);
        printf("  Please check your account number.\n");
        return 0;
    }

    if (!verify_pin(account_index)) {
        return 0;
    }

    current_user = &accounts[account_index];

    printf("\n  Login successful!\n");
    printf("  ----------------------------------------\n");
    printf("  Welcome, %s!\n", current_user->name);
    printf("  Account Number: %d\n", current_user->account_number);
    printf("  ----------------------------------------\n");

    return 1;
}

void logout(int *logged_in) {
    if (*logged_in) {
        printf("\n  Goodbye, %s!\n", current_user->name);
        current_user = NULL;
        *logged_in   = 0;
        printf("  Logged out successfully!\n");
    } else {
        printf("\n  You are not logged in!\n");
    }
}

int is_logged_in() {
    return (current_user != NULL);
}