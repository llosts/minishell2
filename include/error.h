/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** error.h
*/

#ifndef ERROR_H_
    #define ERROR_H_

    #define FAILURE 84
    #define SUCCESS 0

void display_help(void);
int print_error(const char *message, int return_value);

#endif
