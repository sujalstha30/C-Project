#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for account (like a template)
struct Account {
    int account_number;      // Account number
    char name[50];           // Customer name
    int pin;                 // 4-digit PIN
    float balance;           // Money in account
    int transaction_count;   // How many transactions
};

// Structure for transaction (what you did)
struct Transaction {
    int account_number;
    char type[20];           // "DEPOSIT" or "WITHDRAW"
    float amount;
    float balance_after;
    char date[30];
};

// Global variables
struct Account accounts[100];  // Can store 100 accounts
int total_accounts = 0;        // How many accounts exist
struct Account *current_user = NULL;  // Who is logged in

// Function declarations (telling C what functions exist)
void load_accounts();
void save_accounts();
void create_account();
int login();
void check_balance();
void deposit();
void withdraw();
void view_transactions();
void save_transaction(char type[], float amount);
void show_menu();
void clear_screen();

// Main function - Program starts here
int main() {
    int choice;
    int logged_in = 0;
    
    printf("========================================\n");
    printf("    WELCOME TO MY ATM SIMULATOR\n");
    printf("========================================\n\n");
    
    load_accounts();  // Load saved accounts from file
    
    while(1) {  // Loop forever until user exits
        show_menu();
        printf("Enter your choice (1-8): ");
        scanf("%d", &choice);
        getchar();  // Clear newline from buffer
        
        switch(choice) {
            case 1:
                create_account();
                break;
            case 2:
                logged_in = login();
                break;
            case 3:
                if(logged_in) {
                    check_balance();
                } else {
                    printf("\nPlease login first!\n");
                }
                break;
            case 4:
                if(logged_in) {
                    withdraw();
                } else {
                    printf("\n Please login first!\n");
                }
                break;
            case 5:
                if(logged_in) {
                    deposit();
                } else {
                    printf("\n Please login first!\n");
                }
                break;
            case 6:
                if(logged_in) {
                    view_transactions();
                } else {
                    printf("\n Please login first!\n");
                }
                break;
            case 7:
                if(logged_in) {
                    current_user = NULL;
                    logged_in = 0;
                    printf("\nLogged out successfully!\n");
                } else {
                    printf("\n You are not logged in!\n");
                }
                break;
            case 8:
                printf("\nThank you for using ATM Simulator!\n");
                printf("Goodbye!\n\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please enter 1-8.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
    
    return 0;
}

// Show the menu
void show_menu() {
    clear_screen();
    printf("\n========================================\n");
    printf("           ATM MAIN MENU\n");
    printf("========================================\n");
    printf("1. Create New Account\n");
    printf("2. Login\n");
    printf("3. Check Balance\n");
    printf("4. Withdraw Money\n");
    printf("5. Deposit Money\n");
    printf("6. View Transactions\n");
    printf("7. Logout\n");
    printf("8. Exit\n");
    printf("========================================\n");
}

// Clear screen (works on most systems)
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Load accounts from file
void load_accounts() {
    FILE *file = fopen("accounts.dat", "rb");
    
    if(file == NULL) {
        // File doesn't exist yet, that's okay
        printf("No existing accounts found. Starting fresh.\n");
        return;
    }
    
    // Read total number of accounts
    fread(&total_accounts, sizeof(int), 1, file);
    
    // Read all accounts
    fread(accounts, sizeof(struct Account), total_accounts, file);
    
    fclose(file);
    printf("Loaded %d existing accounts.\n", total_accounts);
}

// Save accounts to file
void save_accounts() {
    FILE *file = fopen("accounts.dat", "wb");
    
    if(file == NULL) {
        printf("Error saving accounts!\n");
        return;
    }
    
    // Write total number of accounts
    fwrite(&total_accounts, sizeof(int), 1, file);
    
    // Write all accounts
    fwrite(accounts, sizeof(struct Account), total_accounts, file);
    
    fclose(file);
}

// Create new account
void create_account() {
    printf("\n========================================\n");
    printf("        CREATE NEW ACCOUNT\n");
    printf("========================================\n");
    
    if(total_accounts >= 100) {
        printf("Sorry! Maximum accounts reached.\n");
        return;
    }
    
    struct Account new_account;
    
    // Generate account number
    new_account.account_number = 1001 + total_accounts;
    
    // Get customer name
    printf("Enter your name: ");
    fgets(new_account.name, 50, stdin);
    new_account.name[strcspn(new_account.name, "\n")] = 0;  // Remove newline
    
    // Get PIN
    printf("Create a 4-digit PIN: ");
    scanf("%d", &new_account.pin);
    getchar();
    
    // Validate PIN
    if(new_account.pin < 1000 || new_account.pin > 9999) {
        printf("PIN must be 4 digits!\n");
        return;
    }
    
    // Get initial deposit
    printf("Enter initial deposit amount: Rs.");
    scanf("%f", &new_account.balance);
    getchar();
    
    if(new_account.balance < 0) {
        printf(" Amount cannot be negative!\n");
        return;
    }
    
    new_account.transaction_count = 0;
    
    // Add to accounts array
    accounts[total_accounts] = new_account;
    total_accounts++;
    
    // Save to file
    save_accounts();
    
    printf("\nAccount created successfully!\n");
    printf("Your account number is: %d\n", new_account.account_number);
    printf("Please remember this number!\n");
}

// Login to account
int login() {
    int acc_num, pin, attempts = 0;
    
    printf("\n========================================\n");
    printf("              LOGIN\n");
    printf("========================================\n");
    
    printf("Enter account number: ");
    scanf("%d", &acc_num);
    
    // Find account
    int found = -1;
    for(int i = 0; i < total_accounts; i++) {
        if(accounts[i].account_number == acc_num) {
            found = i;
            break;
        }
    }
    
    if(found == -1) {
        printf("\n Account not found!\n");
        getchar();
        return 0;
    }
    
    // Check PIN (3 attempts)
    while(attempts < 3) {
        printf("Enter PIN: ");
        scanf("%d", &pin);
        getchar();
        
        if(accounts[found].pin == pin) {
            current_user = &accounts[found];
            printf("\n✅ Welcome %s!\n", current_user->name);
            return 1;
        } else {
            attempts++;
            printf(" Wrong PIN! %d attempts remaining.\n", 3 - attempts);
        }
    }
    
    printf("\n Too many wrong attempts! Account locked.\n");
    return 0;
}

// Check balance
void check_balance() {
    printf("\n========================================\n");
    printf("          BALANCE INQUIRY\n");
    printf("========================================\n");
    printf("Account Number: %d\n", current_user->account_number);
    printf("Account Holder: %s\n", current_user->name);
    printf("Current Balance: $%.2f\n", current_user->balance);
    printf("========================================\n");
}

// Withdraw money
void withdraw() {
    float amount;
    
    printf("\n========================================\n");
    printf("           WITHDRAW MONEY\n");
    printf("========================================\n");
    printf("Current Balance: $%.2f\n", current_user->balance);
    printf("Enter amount to withdraw: $");
    scanf("%f", &amount);
    getchar();
    
    // Validate amount
    if(amount <= 0) {
        printf(" Amount must be greater than 0!\n");
        return;
    }
    
    if(amount > current_user->balance) {
        printf(" Insufficient balance!\n");
        return;
    }
    
    if((int)amount % 10 != 0) {
        printf("Amount must be multiple of 10!\n");
        return;
    }
    
    // Process withdrawal
    current_user->balance -= amount;
    save_accounts();
    save_transaction("WITHDRAW", amount);
    
    printf("\n Withdrawal successful!\n");
    printf("Amount withdrawn: $%.2f\n", amount);
    printf("Remaining balance: $%.2f\n", current_user->balance);
}

// Deposit money
void deposit() {
    float amount;
    
    printf("\n========================================\n");
    printf("           DEPOSIT MONEY\n");
    printf("========================================\n");
    printf("Current Balance: $%.2f\n", current_user->balance);
    printf("Enter amount to deposit: Rs.");
    scanf("%f", &amount);
    getchar();
    
    // Validate amount
    if(amount <= 0) {
        printf("Amount must be greater than 0!\n");
        return;
    }
    
    // Process deposit
    current_user->balance += amount;
    save_accounts();
    save_transaction("DEPOSIT", amount);
    
    printf("\n Deposit successful!\n");
    printf("Amount deposited: $%.2f\n", amount);
    printf("New balance: $%.2f\n", current_user->balance);
}

// Save transaction to file
void save_transaction(char type[], float amount) {
    FILE *file = fopen("transactions.txt", "a");  // Append mode
    
    if(file == NULL) {
        printf("Warning: Could not save transaction log.\n");
        return;
    }
    
    // Get current time
    time_t now = time(NULL);
    char *date = ctime(&now);
    date[strcspn(date, "\n")] = 0;  // Remove newline
    
    // Write transaction
    fprintf(file, "%d | %s | %s | $%.2f | Balance: $%.2f\n",
            current_user->account_number,
            date,
            type,
            amount,
            current_user->balance);
    
    fclose(file);
    
    current_user->transaction_count++;
}

// View transactions
void view_transactions() {
    printf("\n========================================\n");
    printf("       TRANSACTION HISTORY\n");
    printf("========================================\n");
    
    FILE *file = fopen("transactions.txt", "r");
    
    if(file == NULL) {
        printf("No transactions found.\n");
        return;
    }
    
    char line[200];
    int count = 0;
    int acc_num;
    
    printf("Last 5 transactions:\n\n");
    
    // Read file and show transactions for current user
    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%d", &acc_num);
        
        if(acc_num == current_user->account_number) {
            printf("%s", line);
            count++;
        }
    }
    
    if(count == 0) {
        printf("No transactions yet.\n");
    }
    
    fclose(file);
    printf("========================================\n");
}