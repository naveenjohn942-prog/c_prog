#include <string.h>
#include <stdio.h>
void main()
{
	char name[10],sname[10];
	int l;
	gets(name);
	gets(sname);
	puts(name);
	
	printf("%d",strlen(name));
	printf("\n%d",sizeof(name));
	
//	strcat(name,sname);
//	printf("\n%s",name);
	
//	strcpy(name,sname);
//	printf("\n%s",name);
	
	printf("\n%d",strcmp(name,sname));

	printf("\n%s",strlwr(name));
	printf("\n%s",strupr(sname));
}