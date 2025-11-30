#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 100
#define MAX_ACCOUNTS 50

struct Transaction {
    char type[10];
    float amount;
    char date[20];
};

struct Account {
    int accountNumber;                       
    char name[50];                           
    char accountType[20];                    
    float balance;                           
    float interestRate;                      
    float minBalance;                        
    char creationDate[20];                  
    char lastTransactionDate[20];            
    struct Transaction transactions[MAX_TRANSACTIONS]; 
    int transactionCount;                    
};

struct Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

void getCurrentDate(char buffer[]) {
    time_t t = time(NULL);              
    struct tm tm = *localtime(&t);      
    sprintf(buffer, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

void addTransaction(int accountIndex, char type[], float amount) {
    int tIndex = accounts[accountIndex].transactionCount;
    if(tIndex < MAX_TRANSACTIONS) {
        strcpy(accounts[accountIndex].transactions[tIndex].type, type);
        accounts[accountIndex].transactions[tIndex].amount = amount;
        getCurrentDate(accounts[accountIndex].transactions[tIndex].date);
        accounts[accountIndex].transactionCount++;
        strcpy(accounts[accountIndex].lastTransactionDate, accounts[accountIndex].transactions[tIndex].date);
    } else {
        printf("Transaction history full!\n");
    }
}

void createAccount() {
    if(accountCount >= MAX_ACCOUNTS) {
        printf("Maximum accounts reached.\n");
        return;
    }

    int index = accountCount;
    struct Account acc;
    acc.accountNumber = 1000 + accountCount;
    acc.transactionCount = 0;

    printf("Enter account holder name: ");
    getchar();
    fgets(acc.name, 50, stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';

    printf("Select account type (Savings/Current/FixedDeposit): ");
    scanf("%s", acc.accountType);

    if(strcmp(acc.accountType, "Savings") == 0) {
        acc.minBalance = 1000;
        acc.interestRate = 4;
    } else if(strcmp(acc.accountType, "Current") == 0) {
        acc.minBalance = 5000;
        acc.interestRate = 0;
    } else if(strcmp(acc.accountType, "FixedDeposit") == 0) {
        acc.minBalance = 10000;
        acc.interestRate = 7;
    } else {
        printf("Invalid account type!\n");
        return;
    }

    printf("Enter initial deposit (Minimum $%.2f): ", acc.minBalance);
    scanf("%f", &acc.balance);

    if(acc.balance < acc.minBalance) {
        printf("Deposit less than minimum required balance. Account not created.\n");
        return;
    }

    getCurrentDate(acc.creationDate);
    strcpy(acc.lastTransactionDate, acc.creationDate);
    addTransaction(index, "Deposit", acc.balance);

    accounts[index] = acc;
    accountCount++;
    printf("Account created successfully! Account Number: %d\n", acc.accountNumber);
}

void deposit() {
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    for(int i = 0; i < accountCount; i++) {
        if(accounts[i].accountNumber == accNum) {
            printf("Enter deposit amount: ");
            scanf("%f", &amount);
            accounts[i].balance += amount;           
            addTransaction(i, "Deposit", amount);     
            printf("Deposit successful. New balance: $%.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void withdraw() {
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    for(int i = 0; i < accountCount; i++) {
        if(accounts[i].accountNumber == accNum) {
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);
            if(accounts[i].balance - amount < accounts[i].minBalance) {
                printf("Cannot withdraw. Balance would fall below minimum: $%.2f\n", accounts[i].minBalance);
                return;
            }
            accounts[i].balance -= amount;           
            addTransaction(i, "Withdrawal", amount); 
            printf("Withdrawal successful. New balance: $%.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void displayAccount() {
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    for(int i = 0; i < accountCount; i++) {
        if(accounts[i].accountNumber == accNum) {
            struct Account a = accounts[i];
            printf("\nAccount Number: %d\n", a.accountNumber);
            printf("Name: %s\n", a.name);
            printf("Type: %s\n", a.accountType);
            printf("Balance: $%.2f\n", a.balance);
            printf("Interest Rate: %.2f%%\n", a.interestRate);
            printf("Account Created: %s\n", a.creationDate);
            printf("Last Transaction: %s\n", a.lastTransactionDate);
            printf("Transaction History:\n");
            for(int j = 0; j < a.transactionCount; j++) {
                printf("%s - %s: $%.2f\n", a.transactions[j].date, a.transactions[j].type, a.transactions[j].amount);
            }
            return;
        }
    }
    printf("Account not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n--- Bank Account Management ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display Account Details\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: displayAccount(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);

    return 0;
}
