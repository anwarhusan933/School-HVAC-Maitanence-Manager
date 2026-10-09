#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
// read integer
int read_integer(char *prompt)
{
    int integer;
    printf("%s",prompt);
    if(scanf("%d",&integer) == 1)
    {
        char ch;
        if(scanf("%c",&ch) == 1)
        {
            printf("Error! Enter only integer.\n");
        }
    }

    return integer;

}
#endif