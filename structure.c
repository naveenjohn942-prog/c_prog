#include<stdio.h>
//prog to store the register no. and 3 sub marks of 10 students and display the total marks of each student and the avg marks of the class

struct student{
	int reg_no;
	char name[20];
	int mark[3];
	
};

int main()
{
	struct student s1[10];
	int i;
	int subsum;
	int average;
	for(i=0;i<2;i++){
		
		printf("Enter name:");
		scanf("%s", s1[i].name);
		
		printf("\nEnter register number:");
		scanf("%d",&s1[i].reg_no);
		for(int j=0;j<3;j++){
			printf("\nEnter marks %d of student %d:",j+1,i+1);
			scanf("%d",&s1[i].mark[j]);
		}
	}
	for(i=0;i<2;i++){
		for(int j=0;j<3;j++){
			subsum+=s1[i].mark[j];
		}
		printf("\n total marks of student%d=%d",i,subsum);
		average+=subsum;
		
		subsum=0;
	}
	printf("\nAverage=%d",average);
	
	for(i=0;i<10;i++){
		
		printf("\nName of the student%d:%s",i+1,s1[i].name);
		printf("\n Register no:%d",s1[i].reg_no);
		for(int j=0;j<3;j++){
			printf("\nMarks%d=%d",j+1,s1[i].mark[j]);
			
		}
	}
	return 0;
}

