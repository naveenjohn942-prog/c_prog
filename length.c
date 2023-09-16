#include <stdio.h>

int main()
{
	int count=0;
	int i;
	char text[20],text2[20];
	
	scanf("%s",text);
	
	for(i=0;text[i]!=0;i++){
		count++;
		text2[i]=text[i];
	}
	printf("%d",count);
	printf("\n%s",text2);
}