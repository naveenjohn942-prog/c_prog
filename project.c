#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PHONE_NUMBER_LENGTH 10
#define MAX_NAME_LENGTH 50
#define FILE_NAME "subscriber_data.dat"

struct subscriber {
    char phonenumber[PHONE_NUMBER_LENGTH + 1]; // +1 for null terminator
    char name[MAX_NAME_LENGTH];
    float amount;
};

// Function prototypes
void addRecord();
void listRecords();
void modifyRecord();
void searchRecord();
void makePayment();
int isPhoneNumberValid(const char *phone);
int isStringValid(const char *str);

int main() {
    int choice;

    printf("\n\n\n\n\n\n\n\n\n**************************************************************");
    printf("\n\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM---");
    printf("\n\t\t****************************************************************");

    while (1) {
        printf("\n Menu:\n 1: Add new record\n 2: List records\n 3: Modify record\n 4: Make payment\n 5: Search records\n 6: Exit\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                listRecords();
                break;
            case 3:
                modifyRecord();
                break;
            case 4:
                makePayment();
                break;
            case 5:
                searchRecord();
                break;
            case 6:
                printf("\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICE\n");
                exit(0);
            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    }

    return 0;
}

int isPhoneNumberValid(const char *phone) {
    // Check if the phone number has exactly 10 digits
    return (strlen(phone) == PHONE_NUMBER_LENGTH && strspn(phone, "0123456789") == PHONE_NUMBER_LENGTH);
}

void addRecord() {
    FILE *file = fopen(FILE_NAME, "ab+");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;

    printf("\nEnter phone number (10 digits only): ");
    scanf("%s", s.phonenumber);
    if (!isPhoneNumberValid(s.phonenumber)) {
        printf("Invalid phone number format. Please enter 10 digits.\n");
        fclose(file);
        return;
    }

    printf("Enter name: ");
    scanf(" %[^\n]s", s.name); // Read the name with spaces
    if (strlen(s.name) >= MAX_NAME_LENGTH) {
        printf("Name is too long. Maximum name length is %d characters.\n", MAX_NAME_LENGTH - 1);
        fclose(file);
        return;
    }

    printf("Enter amount: ");
    scanf("%f", &s.amount);

    fwrite(&s, sizeof(struct subscriber), 1, file);

    fclose(file);
    printf("Record successfully added.\n");
}

void listRecords() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;
    printf("\nPhone Number\t\tUser Name\t\tAmount\n");
    printf("----------------------------------------------\n");

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        printf("%-20s%-20sRs. %.2f\n", s.phonenumber, s.name, s.amount);
    }

    fclose(file);
}

void searchRecord() {
    char phonenumber[PHONE_NUMBER_LENGTH + 1];
    printf("\nEnter phone number to search (10 digits only): ");
    scanf("%s", phonenumber);
    if (!isPhoneNumberValid(phonenumber)) {
        printf("Invalid phone number format. Please enter 10 digits.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;
    int found = 0;

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        if (strcmp(s.phonenumber, phonenumber) == 0) {
            printf("\nRecord Found:\n");
            printf("Phone Number: %s\nName: %s\nAmount: Rs. %.2f\n", s.phonenumber, s.name, s.amount);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRequested Phone Number not found in our database.\n");
    }

    fclose(file);
}

void modifyRecord() {
    char phonenumber[PHONE_NUMBER_LENGTH + 1];
    printf("\nEnter phone number to modify (10 digits only): ");
    scanf("%s", phonenumber);
    if (!isPhoneNumberValid(phonenumber)) {
        printf("Invalid phone number format. Please enter 10 digits.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;
    int found = 0;

    long int offset = -sizeof(struct subscriber); // Define offset as long int

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        if (strcmp(s.phonenumber, phonenumber) == 0) {
            printf("\nEnter new phone number (10 digits only): ");
            scanf("%s", s.phonenumber);
            if (!isPhoneNumberValid(s.phonenumber)) {
                printf("Invalid phone number format. Please enter 10 digits.\n");
                fclose(file);
                return;
            }

            printf("Enter new name: ");
            scanf(" %[^\n]s", s.name); // Read the name with spaces
            if (strlen(s.name) >= MAX_NAME_LENGTH) {
                printf("Name is too long. Maximum name length is %d characters.\n", MAX_NAME_LENGTH - 1);
                fclose(file);
                return;
            }

            printf("Enter new amount: ");
            scanf("%f", &s.amount);

            fseek(file, offset, SEEK_CUR);
            fwrite(&s, sizeof(struct subscriber), 1, file);

            printf("Record successfully modified.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRequested Phone Number not found in our database.\n");
    }

    fclose(file);
}

void makePayment() {
    char phonenumber[PHONE_NUMBER_LENGTH + 1];
    printf("\nEnter phone number for payment: ");
    scanf("%s", phonenumber);

    if (!isPhoneNumberValid(phonenumber)) {
        printf("Invalid phone number format. Please enter 10 digits.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "rb+");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;
    int found = 0;

    long int offset = -sizeof(struct subscriber); // Define offset as long int

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        if (strcmp(s.phonenumber, phonenumber) == 0) {
            printf("\nPhone Number: %s\nName: %s\nCurrent Amount: Rs. %.2f\n", s.phonenumber, s.name, s.amount);
            float paymentAmount;
            printf("Enter payment amount: ");
            scanf("%f", &paymentAmount);

            if (paymentAmount <= s.amount) {
                s.amount -= paymentAmount;
                fseek(file, offset, SEEK_CUR);
                fwrite(&s, sizeof(struct subscriber), 1, file);

                printf("Payment successful. Updated amount: Rs. %.2f\n", s.amount);
            } else {
                printf("Payment amount exceeds the current balance. Payment not accepted.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRequested Phone Number not found in our database.\n");
    }

    fclose(file);
}

