/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** print a string
*/

#include <unistd.h>

#include "my.h"

int my_putstr(char const *str)
{
    int lenght = 0;

    if (str == NULL)
        return 84;
    lenght = my_strlen(str);
    write(1, str, lenght);
    return 0;
}
