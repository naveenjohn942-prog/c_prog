//store 10 student name in a file and read the file
#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *ptr;
    char data[10];
    ptr=fopen("readme.txt","w");

    if(ptr==NULL){
        printf("failed");
        exit(0);
    }
    else{
        for(int i=0;i<5;i++){
            printf("Enter the name");
            scanf("%s",&data);

            fprintf(ptr,"\n%s",data);
            
        }
        fclose(ptr);
        printf("Data successfully read from file GfgTest.c\n");
        printf("The file is now closed.");
    }
    ptr=fopen("readme.txt","r");
    for(int i=0;i<5;i++){
            fscanf(ptr,"\n%s",&data);
            printf("\nname are:%s",data);
        }
    fclose(ptr);
    return 0;
    
}

