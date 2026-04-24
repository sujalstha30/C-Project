#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "transaction.h"
#include "account.h"
#include "ui.h"

void get_current_datetime(char datetime[]) {
    time_t now      = time(NULL);
    char  *time_str = ctime(&now);
    strncpy(datetime, time_str, 29);
    datetime[strcspn(datetime, "\n")] = 0;
}

void save_transaction(char type[], float amount) {
    FILE *file;
    char  datetime[30];

    file = fopen(TRANSACTION_FILE, "a");

    if (file == NULL) {
        printf("\n  Warning: Could not save transaction record.\n");
        return;
    }

    get_current_datetime(datetime);

    fprintf(file, "%d | %s | %-8s | Rs. %8.2f | Balance: Rs. %.2f\n",
            current_user->account_number,
            datetime,
            type,
            amount,
            current_user->balance);

    fclose(file);

    current_user->transaction_count++;
}

void view_transactions() {
    FILE *file;
    char  line[LINE_LENGTH];
    int   acc_num;
    int   count = 0;

    print_header("TRANSACTION HISTORY");

    printf("  Account : %d - %s\n\n",
           current_user->account_number,
           current_user->name);

    file = fopen(TRANSACTION_FILE, "r");

    if (file == NULL) {
        printf("  No transaction history found.\n");
        return;
    }

    printf("  %-4s %-24s %-8s %12s  %s\n",
           "No.", "Date", "Type", "Amount", "Balance");
    printf("  ----------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d", &acc_num);

        if (acc_num == current_user->account_number) {
            count++;
            printf("  %3d. %s", count, line);
        }
    }

    if (count == 0) {
        printf("  No transactions found for this account.\n");
    } else {
        printf("  ----------------------------------------------------------------\n");
        printf("  Total transactions shown: %d\n", count);
    }

    fclose(file);
}