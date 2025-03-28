/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** concatenate two string together
*/

#include <stddef.h>

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    if (dest == NULL)
        return NULL;
    if (src == NULL)
        return dest;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i += 1;
    }
    dest[dest_len + i] = '\0';
    return dest;
}
