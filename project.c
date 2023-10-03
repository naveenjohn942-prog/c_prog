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
void deleteRecord();
int isPhoneNumberValid(const char *phone);
int isStringValid(const char *str);

int main() {
    int choice;

    printf("\n\n\n\n\n\n\n\n\n**************************************************************");
    printf("\n\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM---");
    printf("\n\t\t****************************************************************");

    while (1) {
        printf("\n Menu:\n 1: Add new record\n 2: List records\n 3: Modify record\n 4: Make payment\n 5: Search records\n 6: Delete record\n 7: Exit\n");
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
                deleteRecord();
                break;
            case 7:
                printf("\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICE\n");
                exit(0);
            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    }

    return 0;
}



void deleteRecord() {
    char phonenumber[PHONE_NUMBER_LENGTH + 1];
    printf("\nEnter phone number to delete (10 digits only): ");
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

    FILE *tempFile = fopen("temp.dat", "wb"); // Temporary file to store records without the deleted one

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        if (strcmp(s.phonenumber, phonenumber) == 0) {
            found = 1;
            continue; // Skip writing this record to the temporary file
        }

        fwrite(&s, sizeof(struct subscriber), 1, tempFile); // Write other records to the temporary file
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_NAME);           // Remove the original file
        rename("temp.dat", FILE_NAME); // Rename the temporary file to the original file
        printf("\nRecord with phone number %s has been deleted.\n", phonenumber);
    } else {
        printf("\nRequested Phone Number not found in our database. No records deleted.\n");
        remove("temp.dat"); // Remove the temporary file if no records were deleted
    }
}


int isPhoneNumberValid(const char *phone) {
    return (strlen(phone) == PHONE_NUMBER_LENGTH && strspn(phone, "0123456789") == PHONE_NUMBER_LENGTH);
}

int isStringValid(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0; // Non-alphabetic character found
        }
    }
    return 1; // All characters are alphabetic or spaces
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

    // Check if the phone number already exists
    FILE *existingFile = fopen(FILE_NAME, "rb");
    if (existingFile != NULL) {
        struct subscriber existing;
        while (fread(&existing, sizeof(struct subscriber), 1, existingFile)) {
            if (strcmp(existing.phonenumber, s.phonenumber) == 0) {
                printf("Phone number already exists in the database. Record not added.\n");
                fclose(file);
                fclose(existingFile);
                return;
            }
        }
        fclose(existingFile);
    }

    printf("Enter name: ");
    scanf(" %[^\n]s", s.name);
    if (!isStringValid(s.name)) {
        printf("Invalid name format. Please enter alphabetic characters and spaces only.\n");
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



void searchRecordByName() {
    char searchName[MAX_NAME_LENGTH + 1];
    printf("\nEnter name to search: ");
    scanf(" %[^\n]s", searchName);
    
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;
    int found = 0;

    printf("\nSearch Results by Name:\n");
    printf("Phone Number\t\tUser Name\t\tAmount\n");
    printf("----------------------------------------------\n");

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        if (strstr(s.name, searchName) != NULL) {
            printf("%-20s%-20sRs. %.2f\n", s.phonenumber, s.name, s.amount);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo records found for the provided name.\n");
    }

    fclose(file);
}

void searchRecordByNumber() {
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
            printf("\nSearch Results by Phone Number:\n");
            printf("Phone Number\t\tUser Name\t\tAmount\n");
            printf("----------------------------------------------\n");
            printf("%-20s%-20sRs. %.2f\n", s.phonenumber, s.name, s.amount);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRequested Phone Number not found in our database.\n");
    }

    fclose(file);
}

void searchRecordByAmountRange() {
    float minAmount, maxAmount;
    printf("\nEnter minimum amount: ");
    scanf("%f", &minAmount);
    printf("Enter maximum amount: ");
    scanf("%f", &maxAmount);

    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        exit(1);
    }

    struct subscriber s;
    int found = 0;

    printf("\nSearch Results by Amount Range:\n");
    printf("Phone Number\t\tUser Name\t\tAmount\n");
    printf("----------------------------------------------\n");

    while (fread(&s, sizeof(struct subscriber), 1, file)) {
        if (s.amount >= minAmount && s.amount <= maxAmount) {
            printf("%-20s%-20sRs. %.2f\n", s.phonenumber, s.name, s.amount);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo records found within the specified amount range.\n");
    }

    fclose(file);
}

void searchRecord() {
    int subChoice;

    while (1) {
        printf("\nSearch Options:\n");
        printf("1: Search by Name\n");
        printf("2: Search by Phone Number\n");
        printf("3: Search by Amount Range\n");
        printf("4: Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &subChoice);

        switch (subChoice) {
            case 1:
                searchRecordByName();
                break;
            case 2:
                searchRecordByNumber();
                break;
            case 3:
                searchRecordByAmountRange();
                break;
            case 4:
                return; // Return to the main menu
            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    }
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
            scanf(" %[^\n]s", s.name);
            if (!isStringValid(s.name)) {
                printf("Invalid name format. Please enter alphabetic characters and spaces only.\n");
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
