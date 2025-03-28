/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Parser for command lines
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "my.h"
#include "error.h"
#include "minishell.h"
#include "minishell2.h"

void free_token_list(token_list_t *head)
{
    token_list_t *temp = NULL;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->token);
        free(temp);
    }
}

command_t *create_command(void)
{
    command_t *cmd = malloc(sizeof(command_t));

    if (!cmd)
        return NULL;
    cmd->args = malloc(sizeof(char *) * 64);
    if (!cmd->args) {
        free(cmd);
        return NULL;
    }
    cmd->arg_count = 0;
    cmd->in_file = NULL;
    cmd->out_file = NULL;
    cmd->append = false;
    cmd->heredoc = false;
    cmd->piped = false;
    return cmd;
}

void free_command(command_t *cmd)
{
    if (!cmd)
        return;
    for (int i = 0; i < cmd->arg_count; i++)
        free(cmd->args[i]);
    free(cmd->args);
    free(cmd->in_file);
    free(cmd->out_file);
    free(cmd);
}

void free_command_list(command_list_t *head)
{
    command_list_t *temp = NULL;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free_command(temp->cmd);
        free(temp);
    }
}
