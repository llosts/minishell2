/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** count the lenght of a string
*/

#include <stdlib.h>

int my_strlen(char const *str)
{
    int lenght = 0;

    if (str == NULL)
        return 0;
    while (str[lenght] != '\0')
        lenght += 1;
    return lenght;
}
