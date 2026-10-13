#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// read integer
int get_integer(char *prompt)
{
    long value;
    char line[100];
    char *endptr;
    int attempt_counter = 0;
    while (1)
    {
        errno = 0;
        if (attempt_counter == 3)
        {
            return -1;
        }
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Input error or end of input.\n");
            exit(1);
        }
        value = strtol(line, &endptr, 10);
        if (endptr == line || *endptr != '\n' && *endptr != '\0')
        {
            printf("Invalid input. Please enter only a whole number.\n");
            attempt_counter++;
            continue;
        }
        if (errno == ERANGE)
        {
            printf("Number is too long.\n");
            attempt_counter++;
            continue;
        }
        return (int)value;
    }
}

// read float

#endif