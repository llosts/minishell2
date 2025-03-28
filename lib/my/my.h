/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** header file for my lib
*/

#ifndef MY_H_
    #define MY_H_

char *my_strdup(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *str1, char const *str2, int n);
int my_strlen(char const *str);
int my_putstr(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strchr(const char *str, int c);
char *my_strtok(char *str, const char *delim);
char **my_str_to_word_array(char const *str, char const *delim);
int my_isalpha(char c);
int my_isalnum(char c);

#endif
