/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Command execution logic
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "my.h"
#include "error.h"
#include "minishell.h"
#include "minishell2.h"

int check_and_execute_builtin(shell_state_t *shell, command_t *cmd)
{
    for (int i = 0; builtin_handler[i].name != NULL; i++) {
        if (my_strcmp(cmd->args[0], builtin_handler[i].name) == 0) {
            return builtin_handler[i].func(shell, cmd->args);
        }
    }
    return -1;
}

int execute_simple_command(shell_state_t *shell, command_t *cmd)
{
    int result = 0;
    int stdin_copy = -1;
    int stdout_copy = -1;

    if (!cmd || !cmd->args || !cmd->args[0])
        return 0;
    if (setup_redirections(cmd, &stdin_copy, &stdout_copy) == -1)
        return 1;
    result = check_and_execute_builtin(shell, cmd);
    if (result != -1) {
        reset_redirections(stdin_copy, stdout_copy);
        return result;
    }
    result = execute_single_command(shell, cmd->args);
    reset_redirections(stdin_copy, stdout_copy);
    return result;
}

static command_list_t *move_to_next_command_set(command_list_t *current)
{
    while (current && current->cmd->piped)
        current = current->next;
    if (current)
        current = current->next;
    return current;
}

int execute_commands(shell_state_t *shell, command_list_t *cmd_list)
{
    int result = 0;
    command_list_t *current = cmd_list;

    while (current != NULL) {
        if (current->cmd->piped) {
            result = execute_piped_commands(shell, current);
            current = move_to_next_command_set(current);
        } else {
            result = execute_simple_command(shell, current->cmd);
            current = current->next;
        }
    }
    return result;
}

int execute_command_line(shell_state_t *shell, char *input)
{
    token_list_t *tokens = parse_command_line(input);
    command_list_t *commands = NULL;
    int result = 0;

    if (!tokens)
        return SUCCESS;
    commands = build_command_list(tokens);
    free_token_list(tokens);
    if (!commands)
        return SUCCESS;
    result = execute_commands(shell, commands);
    shell->last_exit_status = result;
    free_command_list(commands);
    return SUCCESS;
}
