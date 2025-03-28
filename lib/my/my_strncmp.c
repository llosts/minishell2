/*
** EPITECH PROJECT, 2024
** my_strncmp
** File description:
** compare two string for n character
*/

int my_strncmp(char const *str1, char const *str2, int n)
{
    int index = 0;

    while (index < n && str1[index] != '\0' && str2[index] != '\0') {
        if (str1[index] != str2[index])
            return str1[index] - str2[index];
        index += 1;
    }
    if (index < n)
        return str1[index] - str2[index];
    return 0;
}
