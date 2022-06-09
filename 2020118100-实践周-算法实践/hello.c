#include <stdio.h>

int main(int argc, char const *argv[])
{
    char name[20];
    printf("Please input your name: ");
    scanf("%s", name);
    printf("Hello, %s!\n", name);
    return 0;
}
