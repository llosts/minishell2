/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-nathan.cheynet
** File description:
** shell.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "my.h"
#include "error.h"
#include "minishell.h"
#include "minishell2.h"
#include "bonus.h"

void display_prompt(env_node_t *env_list)
{
    char *user = get_env_value(env_list, "USER");
    char *cwd = getcwd(NULL, 0);

    if (!user)
        user = "null";
    if (!cwd)
        cwd = "/";
    my_putstr(TURQUOISE);
    my_putstr(user);
    my_putstr("@minishell" RESET);
    my_putstr(":");
    my_putstr(GREEN);
    my_putstr(cwd);
    my_putstr(BLUE ":$> ");
    free(cwd);
}

int handle_builtin(shell_state_t *shell, char *input)
{
    int index = 0;
    char **args = parse_input(input);

    if (args[0] == NULL) {
        free_array(args);
        return SUCCESS;
    }
    while (builtin_handler[index].name != NULL) {
        if (my_strcmp(args[0], builtin_handler[index].name) == 0) {
            shell->last_exit_status = builtin_handler[index].func(shell, args);
            free_array(args);
            return SUCCESS;
        }
        index++;
    }
    shell->last_exit_status = execute_single_command(shell, args);
    free_array(args);
    return SUCCESS;
}

int handle_input(shell_state_t *shell, char *input)
{
    int result = 0;

    if (!input || input[0] == '\0')
        return SUCCESS;
    if (input[my_strlen(input) - 1] == '\n')
        input[my_strlen(input) - 1] = '\0';
    if (my_strcmp(input, "exit") == 0) {
        if (isatty(STDIN_FILENO))
            my_putstr("exit\n");
        return FAILURE;
    }
    result = execute_command_line(shell, input);
    return result;
}

void start_minishell(shell_state_t *shell)
{
    char *input = NULL;
    size_t len = 0;
    int result = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            display_prompt(shell->env_list);
        if (getline(&input, &len, stdin) == -1) {
            my_putstr("\n");
            break;
        }
        result = handle_input(shell, input);
        if (result == FAILURE)
            break;
    }
    free(input);
}
