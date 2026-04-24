#ifndef TRANSACTION_H
#define TRANSACTION_H

#define TRANSACTION_FILE  "transactions.txt"
#define MAX_RECENT         5
#define LINE_LENGTH      200

struct Transaction {
    int   account_number;
    char  type[20];
    float amount;
    float balance_after;
    char  date[30];
};

void save_transaction(char type[], float amount);
void view_transactions();
void get_current_datetime(char datetime[]);

#endif