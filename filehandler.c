#include <stdio.h>
#include "filehandler.h"
#include "account.h"

void load_accounts() {
    FILE *file;

    file = fopen(ACCOUNTS_FILE, "rb");

    if (file == NULL) {
        printf("  Starting with no existing accounts.\n");
        total_accounts = 0;
        return;
    }

    fread(&total_accounts, sizeof(int), 1, file);
    fread(accounts, sizeof(struct Account), total_accounts, file);

    fclose(file);

    printf("  Loaded %d account(s) from storage.\n", total_accounts);
}

void save_accounts() {
    FILE *file;

    file = fopen(ACCOUNTS_FILE, "wb");

    if (file == NULL) {
        printf("\n  ERROR: Could not save accounts to file!\n");
        printf("  Data may be lost when program closes.\n");
        return;
    }

    fwrite(&total_accounts, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct Account), total_accounts, file);

    fclose(file);
}