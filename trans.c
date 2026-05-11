#include <stdio.h>
#include <stdlib.h>

struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

// Function prototypes
unsigned int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);
void listAccounts(FILE *fPtr);

int main()
{
    FILE *cfPtr;
    unsigned int choice;

    // Open file
    cfPtr = fopen("credit.dat", "rb+");

    if (cfPtr == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    while ((choice = enterChoice()) != 6)
    {
        switch (choice)
        {
            case 1:
                textFile(cfPtr);
                break;

            case 2:
                updateRecord(cfPtr);
                break;

            case 3:
                newRecord(cfPtr);
                break;

            case 4:
                deleteRecord(cfPtr);
                break;

            case 5:
                listAccounts(cfPtr);
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    fclose(cfPtr);

    return 0;
}

// Menu function
unsigned int enterChoice(void)
{
    unsigned int choice;

    printf("\n===== BANK ACCOUNT MENU =====\n");
    printf("1 - Generate accounts.txt\n");
    printf("2 - Update account\n");
    printf("3 - Add new account\n");
    printf("4 - Delete account\n");
    printf("5 - List all accounts\n");
    printf("6 - Exit\n");
    printf("Enter your choice: ");

    scanf("%u", &choice);

    return choice;
}

// Generate text file
void textFile(FILE *readPtr)
{
    FILE *writePtr;
    struct clientData client;

    writePtr = fopen("accounts.txt", "w");

    if (writePtr == NULL)
    {
        printf("Cannot create accounts.txt\n");
        return;
    }

    rewind(readPtr);

    fprintf(writePtr,
            "%-6s%-15s%-15s%-10s\n",
            "Acct",
            "Last Name",
            "First Name",
            "Balance");

    while (fread(&client,
                 sizeof(struct clientData),
                 1,
                 readPtr) == 1)
    {
        if (client.acctNum != 0)
        {
            fprintf(writePtr,
                    "%-6u%-15s%-15s%.2lf\n",
                    client.acctNum,
                    client.lastName,
                    client.firstName,
                    client.balance);
        }
    }

    fclose(writePtr);

    printf("accounts.txt generated successfully.\n");
}

// Add new record
void newRecord(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter account number (1-100): ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > 100)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists.\n");
    }
    else
    {
        printf("Enter lastname firstname balance:\n");

        scanf("%14s %9s %lf",
              client.lastName,
              client.firstName,
              &client.balance);

        client.acctNum = accountNum;

        fseek(fPtr,
              (accountNum - 1) * sizeof(struct clientData),
              SEEK_SET);

        fwrite(&client,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Account added successfully.\n");
    }
}

// Update account
void updateRecord(FILE *fPtr)
{
    struct clientData client;

    unsigned int account;
    double transaction;

    printf("Enter account number to update: ");
    scanf("%u", &account);

    if (account < 1 || account > 100)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (account - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
    }
    else
    {
        printf("Current Balance: %.2lf\n",
               client.balance);

        printf("Enter amount (+deposit / -withdraw): ");
        scanf("%lf", &transaction);

        client.balance += transaction;

        fseek(fPtr,
              -(long)sizeof(struct clientData),
              SEEK_CUR);

        fwrite(&client,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Updated Balance: %.2lf\n",
               client.balance);
    }
}

// Delete record
void deleteRecord(FILE *fPtr)
{
    struct clientData client;
    struct clientData blankClient = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter account number to delete: ");
    scanf("%u", &accountNum);

    if (accountNum < 1 || accountNum > 100)
    {
        printf("Invalid account number.\n");
        return;
    }

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
    }
    else
    {
        fseek(fPtr,
              (accountNum - 1) * sizeof(struct clientData),
              SEEK_SET);

        fwrite(&blankClient,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Account deleted successfully.\n");
    }
}

// List all accounts
void listAccounts(FILE *fPtr)
{
    struct clientData client;

    rewind(fPtr);

    printf("\n%-6s %-15s %-15s %-10s\n",
           "Acct",
           "Last Name",
           "First Name",
           "Balance");

    while (fread(&client,
                 sizeof(struct clientData),
                 1,
                 fPtr) == 1)
    {
        if (client.acctNum != 0)
        {
            printf("%-6u %-15s %-15s %.2lf\n",
                   client.acctNum,
                   client.lastName,
                   client.firstName,
                   client.balance);
        }
    }
}