/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** copy a string and return it
*/

#include <stddef.h>

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (src == NULL)
        return NULL;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
    return dest;
}
