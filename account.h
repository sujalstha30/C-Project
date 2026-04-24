#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_ACCOUNTS     100
#define NAME_LENGTH       50
#define MIN_PIN         1000
#define MAX_PIN         9999
#define BASE_ACCOUNT_NUM 1001

struct Account {
    int   account_number;
    char  name[NAME_LENGTH];
    int   pin;
    float balance;
    int   transaction_count;
};

extern struct Account accounts[MAX_ACCOUNTS];
extern int            total_accounts;
extern struct Account *current_user;

void create_account();
void check_balance();
void deposit();
void withdraw();
int  find_account(int acc_num);
int  generate_account_number();
int  validate_pin(int pin);
int  validate_amount(float amount);
int  validate_withdraw_amount(float amount);

#endif