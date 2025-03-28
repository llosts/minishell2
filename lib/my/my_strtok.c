/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-robotfactory-nathan.cheynet
** File description:
** my_strtok.c
*/

#include <stddef.h>

static int is_delimiter(char c, const char *delim)
{
    const char *d = delim;

    while (*d != '\0') {
        if (c == *d) {
            return 1;
        }
        d += 1;
    }
    return 0;
}

static char *skip_delimiters(char *str, const char *delim)
{
    char *current = str;

    while (*current != '\0' && is_delimiter(*current, delim)) {
        current += 1;
    }
    return current;
}

static char *find_token_end(char *str, const char *delim)
{
    char *current = str;

    while (*current != '\0' && !is_delimiter(*current, delim)) {
        current += 1;
    }
    return current;
}

static char **get_next_token_storage(void)
{
    static char *next_token = NULL;

    return &next_token;
}

char *my_strtok(char *str, const char *delim)
{
    char **next_token = get_next_token_storage();
    char *current = (str == NULL) ? *next_token : str;
    char *token_start = NULL;
    char *token_end = NULL;

    if (current == NULL)
        return NULL;
    token_start = skip_delimiters(current, delim);
    if (*token_start == '\0') {
        *next_token = NULL;
        return NULL;
    }
    token_end = find_token_end(token_start, delim);
    if (*token_end == '\0') {
        *next_token = NULL;
    } else {
        *token_end = '\0';
        *next_token = token_end + 1;
    }
    return token_start;
}
