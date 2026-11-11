#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>

#define MAX_ATTEMPTS 3
#define NUMBER_LEN 14
#define LINE_SIZE 127
#define NAME_SIZE 127

int get_integer(const char *prompt, int *result);
int get_string(const char *prompt, char string[], size_t size);
int get_float(const char *prompt, float *result);
int get_phone_number(const char *prompt, char *phone_number, size_t length);
void buffer_flusher(void);

// get integer function
int get_integer(const char *prompt, int *result)
{
    int attempts = 0;
    char line[LINE_SIZE];
    while (attempts < MAX_ATTEMPTS)
    {
        char *endptr = NULL;
        size_t length = 0;
        long value;
        printf("%s", prompt);
        if (fgets(line, sizeof line, stdin) == NULL)
        {
            if (ferror(stdin))
            {
                perror("Input error");
            }
            else
            {
                fprintf(stderr, "End of input.\n");
            }
            return 0;
        }
        length = strlen(line);
        if (length > 0 && line[length - 1] == '\n')
        {
            line[length - 1] = '\0';
        }
        else
        {
            buffer_flusher();
            printf("Input is too long. Please try again.\n");
            attempts++;
            continue;
        }
        if (line[0] == '\0')
        {
            printf("Input cannot be empty.\n");
            attempts++;
            continue;
        }
        errno = 0;
        value = strtol(line, &endptr, 10);
        if (line == endptr || errno == ERANGE)
        {
            printf("Invalid input or integer out of range. Please try again.\n");
            attempts++;
            continue;
        }

        // skip white spaces
        while (isspace((unsigned char)*endptr))
        {
            endptr++;
        }

        if (*endptr != '\0' || value < INT_MIN || value > INT_MAX)
        {
            printf("Please enter a whole number between %d and %d.\n", INT_MIN, INT_MAX);
            attempts++;
            continue;
        }
        *result = (int)value;
        return 1;
    }
    return 0;
}

int get_string(const char *prompt, char string[], size_t size)
{
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        size_t length;
        printf("%s", prompt);
        if (fgets(string, size, stdin) == NULL)
        {
            if (ferror(stdin))
            {
                perror("Input error");
            }
            else
            {
                fprintf(stderr, "End of input.\n");
            }
            return 0;
        }

        length = strlen(string); // get string length

        if (length > 0 && string[length - 1] == '\n')
        {
            string[length - 1] = '\0';
            length--;
        }
        else
        {
            buffer_flusher();
            printf("Input is too long. Please try again.\n");
            attempts++;
            continue;
        }
        if (string[0] == '\0')
        {
            printf("Input can't be empty.\n");
            attempts++;
            continue;
        }
        return 1;
    }
    return 0;
}

// buffer flusher function
void buffer_flusher(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        ;
    }
}

// get float function
int get_float(const char *prompt, float *result)
{
    int attempt = 0;
    while (attempt < 3)
    {
        char line[LINE_SIZE];
        char *endptr;
        double value;
        size_t length;
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            if (ferror(stdin))
            {
                perror("Input error.");
            }
            else
            {
                fprintf(stderr, "End of input.\n");
            }
            return 0;
        }
        length = strlen(line);
        if (length > 0 && line[length - 1] == '\n')
        {
            line[length - 1] = '\0';
            length--;
        }
        else
        {
            buffer_flusher();
        }
        if (line[0] == '\0')
        {
            printf("Input can't be empty.\n");
            attempt++;
            continue;
        }
        errno = 0;

        value = strtod(line, &endptr); // convert string to double
        if (line == endptr || errno == ERANGE)
        {
            printf("Invalid input or out-of-range. please try again.\n");
            attempt++;
            continue;
        }
        // remove space
        if (isspace((unsigned char)*endptr))
        {
            endptr++;
        }
        if (*endptr != '\0' || value < DBL_MIN || value > DBL_MAX)
        {
            printf("Please a real number. Please try again.\n");
            attempt++;
            continue;
        }
        *result = (float)value; // assign float value to result
        return 1;
    }
    return 0;
}

// get phone number function
int get_phone_number(const char *prompt, char *phone_number, size_t length)
{
    int attmpts = 0;
    while (attmpts < MAX_ATTEMPTS)
    {
        size_t number_len = 0;
        int invalid_char = 0;
        printf("%s", prompt);
        if (fgets(phone_number, length, stdin) == NULL)
        {
            if (ferror(stdin))
            {
                perror("Input error");
            }
            else
            {
                fprintf(stderr, "End of input.\n");
            }
            return 0;
        }
        // boffer overflow check
        number_len = strlen(phone_number);
        if (number_len > 0 && phone_number[number_len - 1] == '\n')
        {
            phone_number[number_len - 1] = '\0';
            number_len--;
        }
        else
        {
            buffer_flusher();
            printf("Input is too long. Please try again.\n");
            attmpts++;
            continue;
        }

        // check allowed character
        for(int i = 0; phone_number[i] != '\0'; i++)
        {
            if(phone_number[i] == '+')
            {
                if(i != 0)
                {
                    invalid_char = 1;
                    break;
                }
            }
           else if(isalpha((unsigned char)phone_number[i]))
            {
                invalid_char = 1;
                break;
            }
            else if(isspace((unsigned char)phone_number[i]))
            {
                invalid_char = 1;
                break;
            }
        }
        if(invalid_char)
        {
            printf("Please enter a valid character.\n");
            attmpts++;
            continue;
        }
        number_len = strlen(phone_number);

        if(number_len < 10 || number_len > 10)
        {
            printf("Enter only 10 digits number.\n");
            attmpts++;
            continue;
        }
        return 1;
    }
    return 0;
}

#endif