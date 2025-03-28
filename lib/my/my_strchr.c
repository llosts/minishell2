/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** my_strchr.c
*/

#include <stddef.h>

char *my_strchr(const char *str, int c)
{
    while (*str != '\0') {
        if (*str == c)
            return (char *)str;
        str++;
    }
    return NULL;
}
