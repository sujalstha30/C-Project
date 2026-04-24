#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "transaction.h"
#include "filehandler.h"
#include "ui.h"

struct Account  accounts[MAX_ACCOUNTS];
int             total_accounts = 0;
struct Account *current_user   = NULL;

static float get_initial_deposit() {
    float amount;
    printf("Enter initial deposit amount: Rs. ");
    scanf("%f", &amount);
    getchar();
    return amount;
}

static void get_customer_name(char name[]) {
    printf("Enter your full name: ");
    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
}

int validate_pin(int pin) {
    if (pin < MIN_PIN || pin > MAX_PIN) {
        printf("\n  ERROR: PIN must be exactly 4 digits!\n");
        return 0;
    }
    return 1;
}

int validate_amount(float amount) {
    if (amount <= 0) {
        printf("\n  ERROR: Amount must be greater than zero!\n");
        return 0;
    }
    return 1;
}

int validate_withdraw_amount(float amount) {
    if (!validate_amount(amount)) {
        return 0;
    }
    if ((int)amount % 10 != 0) {
        printf("\n  ERROR: Amount must be a multiple of 10!\n");
        return 0;
    }
    if (amount > current_user->balance) {
        printf("\n  ERROR: Insufficient balance!\n");
        printf("  Available balance: Rs. %.2f\n", current_user->balance);
        return 0;
    }
    return 1;
}

int find_account(int acc_num) {
    int i;
    for (i = 0; i < total_accounts; i++) {
        if (accounts[i].account_number == acc_num) {
            return i;
        }
    }
    return -1;
}

int generate_account_number() {
    return BASE_ACCOUNT_NUM + total_accounts;
}

void create_account() {
    struct Account new_account;
    int   pin;
    float initial_deposit;

    print_header("CREATE NEW ACCOUNT");

    if (total_accounts >= MAX_ACCOUNTS) {
        printf("\n  ERROR: Maximum accounts reached!\n");
        printf("  Cannot create more accounts.\n");
        return;
    }

    new_account.account_number = generate_account_number();

    get_customer_name(new_account.name);

    if (strlen(new_account.name) == 0) {
        printf("\n  ERROR: Name cannot be empty!\n");
        return;
    }

    printf("Create a 4-digit PIN: ");
    scanf("%d", &pin);
    getchar();

    if (!validate_pin(pin)) {
        return;
    }
    new_account.pin = pin;

    initial_deposit = get_initial_deposit();

    if (!validate_amount(initial_deposit)) {
        return;
    }
    new_account.balance = initial_deposit;

    new_account.transaction_count = 0;

    accounts[total_accounts] = new_account;
    total_accounts++;

    save_accounts();

    printf("\n  Account created successfully!\n");
    printf("  ----------------------------------------\n");
    printf("  Account Number : %d\n", new_account.account_number);
    printf("  Account Holder : %s\n", new_account.name);
    printf("  Opening Balance: Rs. %.2f\n", new_account.balance);
    printf("  ----------------------------------------\n");
    printf("  IMPORTANT: Remember your account number!\n");
}

void check_balance() {
    print_header("BALANCE INQUIRY");
    printf("  Account Number : %d\n",   current_user->account_number);
    printf("  Account Holder : %s\n",   current_user->name);
    printf("  ----------------------------------------\n");
    printf("  Current Balance: Rs. %.2f\n", current_user->balance);
    printf("  ----------------------------------------\n");
    printf("  Total Transactions: %d\n", current_user->transaction_count);
}

void deposit() {
    float amount;

    print_header("DEPOSIT MONEY");

    printf("  Current Balance: Rs. %.2f\n\n", current_user->balance);
    printf("  Enter amount to deposit: Rs. ");
    scanf("%f", &amount);
    getchar();

    if (!validate_amount(amount)) {
        return;
    }

    current_user->balance += amount;

    save_accounts();
    save_transaction("DEPOSIT", amount);

    printf("\n  Deposit successful!\n");
    printf("  ----------------------------------------\n");
    printf("  Amount Deposited: Rs. %.2f\n", amount);
    printf("  New Balance     : Rs. %.2f\n", current_user->balance);
    printf("  ----------------------------------------\n");
}

void withdraw() {
    float amount;

    print_header("WITHDRAW MONEY");

    printf("  Current Balance: Rs. %.2f\n\n", current_user->balance);
    printf("  Enter amount to withdraw: Rs. ");
    scanf("%f", &amount);
    getchar();

    if (!validate_withdraw_amount(amount)) {
        return;
    }

    current_user->balance -= amount;

    save_accounts();
    save_transaction("WITHDRAW", amount);

    printf("\n  Withdrawal successful!\n");
    printf("  ----------------------------------------\n");
    printf("  Amount Withdrawn : Rs. %.2f\n", amount);
    printf("  Remaining Balance: Rs. %.2f\n", current_user->balance);
    printf("  ----------------------------------------\n");
}