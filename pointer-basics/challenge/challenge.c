// char a - output address
// char *x - init to variables, output address
// int b - output address
// int *y

#include <stdio.h>

int main()
{  
    char a;
    char *x = &a;
    int b;
    int *y = &b;

    printf("Address of char a: %p\n", &a);
    printf("Address in char *x: %p\n", x);
    printf("Address of int b: %p\n", &b);
    printf("Address in int *y: %p\n", y);

    return 0;
}