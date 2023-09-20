#include<stdio.h>
#include<stdlib.h>

int main()
{
	int x=10;
	int *ptr=&x;
	int **ptr1=&ptr;
	
	printf("%d",x);
	printf("\n%d",*ptr);
	printf("\n%d",**ptr1);
}