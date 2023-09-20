#include <stdio.h>

int main()
{
    int a = 10, b = 20;
    const int *ptr;    
    ptr = &a;    
    ptr = &b;
    printf("%d", *ptr);
    return 0;
}
