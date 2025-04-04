/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Token processing and command building
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "my.h"
#include "error.h"
#include "minishell.h"
#include "minishell2.h"

static void add_command_to_list(command_list_t **head, command_t *cmd)
{
    command_list_t *new_node = malloc(sizeof(command_list_t));
    command_list_t *current = NULL;

    if (!new_node || !cmd)
        return;
    new_node->cmd = cmd;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

static token_list_t *handle_input_redirect(token_list_t *token, command_t *cmd)
{
    cmd->in_file = my_strdup(token->next->token);
    cmd->heredoc = false;
    return token->next;
}

static token_list_t *handle_heredoc_redirect(token_list_t *token,
    command_t *cmd)
{
    cmd->in_file = my_strdup(token->next->token);
    cmd->heredoc = true;
    return token->next;
}

static token_list_t *handle_output_redirect(token_list_t *token,
    command_t *cmd)
{
    cmd->out_file = my_strdup(token->next->token);
    cmd->append = false;
    return token->next;
}

static token_list_t *handle_append_redirect(token_list_t *token,
    command_t *cmd)
{
    cmd->out_file = my_strdup(token->next->token);
    cmd->append = true;
    return token->next;
}

static token_list_t *process_redirect(token_list_t *token, command_t *cmd)
{
    if (!token)
        return NULL;
    if (!token->next) {
        print_error("Missing name for redirect.\n", 1);
        return NULL;
    }
    switch (token->type) {
        case REDIRECT_OUT:
            return handle_output_redirect(token, cmd);
        case REDIRECT_APPEND:
            return handle_append_redirect(token, cmd);
        case REDIRECT_IN:
            return handle_input_redirect(token, cmd);
        case REDIRECT_HEREDOC:
            return handle_heredoc_redirect(token, cmd);
        default:
            return token;
    }
    return NULL;
}

static command_t *finalize_command(command_list_t **cmd_list,
    command_t *current_cmd, token_type_t type)
{
    if (current_cmd->arg_count == 0)
        return current_cmd;
    current_cmd->args[current_cmd->arg_count] = NULL;
    if (type == PIPE)
        current_cmd->piped = true;
    add_command_to_list(cmd_list, current_cmd);
    return create_command();
}

static void process_token(token_list_t **token, command_list_t **cmd_list,
    command_t **current)
{
    char *arg = NULL;
    int len = 0;

    if ((*token)->type == WORD) {
        arg = my_strdup((*token)->token);
        len = my_strlen(arg);
        if (len >= 2 && (arg[0] == '\'' && arg[len - 1] == '\'')) {
            arg[len - 1] = '\0';
            (*current)->args[(*current)->arg_count] = my_strdup(arg + 1);
            free(arg);
        } else
            (*current)->args[(*current)->arg_count] = arg;
        (*current)->arg_count += 1;
    } else if ((*token)->type == SEMICOLON || (*token)->type == PIPE) {
        *current = finalize_command(cmd_list, *current, (*token)->type);
        *current = (!*current) ? *current : create_command();
    } else
        *token = process_redirect(*token, *current);
}

static void finalize_command_list(command_list_t **cmd_list,
    command_t *current_cmd)
{
    if (current_cmd->arg_count > 0) {
        current_cmd->args[current_cmd->arg_count] = NULL;
        add_command_to_list(cmd_list, current_cmd);
    } else {
        free_command(current_cmd);
    }
}

command_list_t *build_command_list(token_list_t *tokens)
{
    command_list_t *cmd_list = NULL;
    command_t *current_cmd = create_command();
    token_list_t *token = tokens;

    if (!current_cmd)
        return NULL;
    while (token != NULL) {
        process_token(&token, &cmd_list, &current_cmd);
        if (!current_cmd) {
            free_command_list(cmd_list);
            return NULL;
        }
        if (!token)
            return NULL;
        token = token->next;
    }
    finalize_command_list(&cmd_list, current_cmd);
    return cmd_list;
}
