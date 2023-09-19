#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *ptr;
    char data[50]; 
    ptr = fopen("readme.txt", "wb");

    if (ptr == NULL) {
        printf("Failed to open file for writing.\n");
        exit(1);
    } else {
        for (int i = 0; i < 10; i++) { 
            printf("Enter the name: ");
            scanf("%s", data);
            fwrite(data, sizeof(char), sizeof(data), ptr); 
        }
        fclose(ptr);
        printf("Data successfully written to file.\n");
    }

    ptr = fopen("readme.txt", "rb");
    if (ptr == NULL) {
        printf("Failed to open file for reading.\n");
        exit(1);
    }

    printf("Names read from file:\n");
    for (int i = 0; i < 10; i++) { 
        fread(data, sizeof(char), sizeof(data), ptr); 
        printf("Name: %s\n", data);
    }
    fclose(ptr);
    return 0;
}
