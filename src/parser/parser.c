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

static bool handle_pipe_token(token_list_t *current, bool *had_word)
{
    token_list_t *next = current->next;

    if (!*had_word)
        return false;
    while (next && next->type != WORD && next->type != PIPE)
        next = next->next;
    if (!next || next->type != WORD)
        return false;
    *had_word = false;
    return true;
}

static bool is_valid_pipe_sequence(token_list_t *tokens)
{
    token_list_t *current = tokens;
    bool had_word = false;

    if (current && current->type == PIPE)
        return false;
    while (current != NULL) {
        if (current->type == WORD)
            had_word = true;
        if (current->type == PIPE && !handle_pipe_token(current, &had_word))
            return false;
        current = current->next;
    }
    return true;
}

bool is_operator(char c)
{
    return (c == ';' || c == '|' || c == '>' || c == '<');
}

bool is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

void add_token(token_list_t **head, char *token, token_type_t type)
{
    token_list_t *new_node = malloc(sizeof(token_list_t));
    token_list_t *current = NULL;

    if (!new_node || !token)
        return;
    new_node->token = my_strdup(token);
    new_node->type = type;
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

void tokenize_input(char *input, token_list_t **head)
{
    int i = 0;
    int start = 0;
    char buffer[1024] = {0};

    while (input[i] != '\0') {
        if (is_space(input[i])) {
            handle_space(input, (int *[2]){&i, &start}, buffer, head);
            continue;
        }
        if (is_operator(input[i]))
            handle_operator(input, &i, &start, head);
        else
            handle_word(input, &i, &start, head);
    }
    if (i > start) {
        my_strncpy(buffer, input + start, i - start);
        buffer[i - start] = '\0';
        add_token(head, buffer, WORD);
    }
}

token_list_t *parse_command_line(char *input)
{
    token_list_t *tokens = NULL;

    if (!input || input[0] == '\0')
        return NULL;
    tokenize_input(input, &tokens);
    if (!is_valid_pipe_sequence(tokens)) {
        print_error("Invalid null command.\n", 1);
        free_token_list(tokens);
        return NULL;
    }
    return tokens;
}
