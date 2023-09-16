#include <stdio.h>
int main()
{
    int n, i;
    float sum;
    sum = 0.0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        sum = sum + ((float)(i) / (float)(fact(i)));
    }
    printf("%f", sum);
    return 0; // Added return statement
}

int fact(int num)
{
    int f, j;
    f = 1;
    for (j = 1; j <= num; j++)
    {
        f = f * j; 
    }
    return f;
}

