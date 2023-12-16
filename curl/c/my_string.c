#include "../h/my_string.h"

int my_strlen(char* str)
{
    int i = 0;
    for (; str[i]; i++) {}
    return i;
}

char* my_strdup(char* dest)
{
    char* src = calloc((my_strlen(dest) + 1), sizeof(char));
    for (int i = 0; dest[i] != '\0'; i++)
    {
        src[i] = dest[i];
    }
    src[my_strlen(dest)] = '\0';
    return src;
}

int my_strcmp(char* dest, char* src)
{
    while (*dest)
    {
        if (*dest != *src)
        {
            break;
        }
        dest++;
        src++;
    }
    return *dest - *src;
}

void my_strcpy(char* dest, char* src)
{
    int length = my_strlen(dest);
    for (int i = 0; i < my_strlen(src); i++)
    {
        dest[length++] = src[i];
    }
}

void fill_null(char* str, int length)
{
    for (int i = 0; i < length; i++)
    {
        str[i] = '\0';
    }
}

void failure_statement(char* message)
{
    write(2, message, my_strlen(message));
    exit(1);
}