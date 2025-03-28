/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** my_isalnum.c
*/

int my_isalnum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}
