/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Help and usage information
*/

#include <unistd.h>

#include "my.h"

void display_help(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./mysh\n\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    mysh is a shell that can run commands, ");
    my_putstr("manage environment variables, and handle\n");
    my_putstr("    pipes (|), semicolons (;), and ");
    my_putstr("redirections (>, <, >>, <<).\n");
}

int print_error(const char *message, int return_value)
{
    write(STDERR_FILENO, message, my_strlen(message));
    return return_value;
}
