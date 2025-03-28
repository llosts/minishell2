/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** allocate a string and return it
*/

#include <stddef.h>
#include <stdlib.h>

#include "my.h"

char *my_strdup(char const *str)
{
    int i = 0;
    char *copy_str = NULL;

    if (str == NULL)
        return NULL;
    copy_str = malloc(sizeof(char) * (my_strlen(str) + 1));
    if (copy_str == NULL)
        return NULL;
    while (str[i] != '\0') {
        copy_str[i] = str[i];
        i += 1;
    }
    copy_str[i] = '\0';
    return copy_str;
}
