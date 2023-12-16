#ifndef _CURL_H_MY_STRING_H_
#define _CURL_H_MY_STRING_H_

#include <stdlib.h>
#include <unistd.h>

// Counts string length.
int my_strlen(char* str);

// Allocates memory and copy the source.
char* my_strdup(char* dest);

// Compares the two string.
int my_strcmp(char* dest, char* src);

// Copy string to dest.
void my_strcpy(char* dest, char* src);

// Stderror message and exit status.
void failure_statement(char* message);

// Fills the '\0' charecters by given length.
void fill_null(char* str, int length);

#endif