/*
** EPITECH PROJECT, 2024
** my_strncpy
** File description:
** copy n character of a string and return it
*/

#include <stddef.h>

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (src == NULL)
        return NULL;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    while (i < n) {
        dest[i] = '\0';
        i += 1;
    }
    return dest;
}
