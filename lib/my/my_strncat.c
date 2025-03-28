/*
** EPITECH PROJECT, 2024
** my_strncat
** File description:
** concatenate n character of two string
*/

#include <stddef.h>

#include "my.h"

char *my_strncat(char *dest, char const *src, int n)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    if (dest == NULL)
        return NULL;
    if (src == NULL)
        return dest;
    while (i < n && src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i += 1;
    }
    dest[dest_len + i] = '\0';
    return dest;
}
