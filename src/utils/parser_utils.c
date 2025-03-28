/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** parser_utils.c
*/

#include <stdbool.h>
#include <stdlib.h>

#include "minishell2.h"
#include "my.h"

static bool is_quote(char c)
{
    return (c == '\'' || c == '"');
}

static token_type_t get_operator_type(char *op)
{
    if (my_strcmp(op, ";") == 0)
        return SEMICOLON;
    if (my_strcmp(op, "|") == 0)
        return PIPE;
    if (my_strcmp(op, ">") == 0)
        return REDIRECT_OUT;
    if (my_strcmp(op, "<") == 0)
        return REDIRECT_IN;
    if (my_strcmp(op, ">>") == 0)
        return REDIRECT_APPEND;
    if (my_strcmp(op, "<<") == 0)
        return REDIRECT_HEREDOC;
    return WORD;
}

static void handle_quoted_word(char *input, int *i, char quote_char)
{
    (*i)++;
    while (input[*i] != '\0' && input[*i] != quote_char)
        (*i)++;
    if (input[*i] == quote_char)
        (*i)++;
}

static void helper_operator(char *input, int *i, char *buffer)
{
    if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i]) {
        buffer[0] = input[*i];
        buffer[1] = input[*i];
        buffer[2] = '\0';
        *i += 2;
    } else {
        buffer[0] = input[*i];
        buffer[1] = '\0';
        (*i)++;
    }
}

void handle_word(char *input, int *i, int *start, token_list_t **head)
{
    char buffer[1024] = {0};
    char quote_char;

    while (input[*i] != '\0' && !is_space(input[*i]) &&
            !is_operator(input[*i])) {
        if (is_quote(input[*i])) {
            quote_char = input[*i];
            handle_quoted_word(input, i, quote_char);
        } else {
            (*i)++;
        }
    }
    my_strncpy(buffer, input + *start, *i - *start);
    buffer[*i - *start] = '\0';
    add_token(head, buffer, WORD);
    *start = *i;
}

void handle_operator(char *input, int *i, int *start,
    token_list_t **head)
{
    char buffer[3] = {0};
    token_type_t type;
    char word[1024] = {0};

    if (*i > *start) {
        my_strncpy(word, input + *start, *i - *start);
        word[*i - *start] = '\0';
        add_token(head, word, WORD);
    }
    helper_operator(input, i, buffer);
    type = get_operator_type(buffer);
    add_token(head, buffer, type);
    *start = *i;
}

void handle_space(char *input, int *i_start[2], char *buffer,
    token_list_t **head)
{
    if (*i_start[0] > *i_start[1]) {
        my_strncpy(buffer, input + *i_start[1], *i_start[0] - *i_start[1]);
        buffer[*i_start[0] - *i_start[1]] = '\0';
        add_token(head, buffer, WORD);
    }
    (*i_start[0])++;
    *i_start[1] = *i_start[0];
}
