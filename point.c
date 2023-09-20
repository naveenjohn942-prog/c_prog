#include<stdio.h>

int main()
{
	int x=10,y=20,*p;
	p=&x;
	y=*p;
	
	printf("\n%p",p);
	printf("\n%p",&x);
	printf("\n%d",&x);//garbage value
	printf("\n%d",*p);
	printf("\n%d",y);//value of x is stored in it 
}