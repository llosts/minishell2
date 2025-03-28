/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** compare two string
*/

#include "my.h"

int my_strcmp(char const *str1, char const *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    int index = 0;
    int ret_value = 0;

    if (len1 != len2)
        ret_value = str1[index] - str2[index];
    while (str1[index] != '\0') {
        if (str1[index] != str2[index]) {
            ret_value = str1[index] - str2[index];
            break;
        }
        index += 1;
    }
    if (ret_value < 0)
        return -1;
    if (ret_value > 0)
        return 1;
    return 0;
}
