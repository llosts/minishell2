/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Extensions for minishell2 (pipes, redirections, etc.)
*/

#include <stdbool.h>
#include <sys/types.h>

#include "minishell.h"

#ifndef MINISHELL2_H_
    #define MINISHELL2_H_

/* Token types for parsing */
typedef enum {
    WORD,
    SEMICOLON,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    REDIRECT_APPEND,
    REDIRECT_HEREDOC
} token_type_t;

/* Linked list to store tokens during parsing */
typedef struct token_list_s {
    char *token;
    token_type_t type;
    struct token_list_s *next;
} token_list_t;

/* Structure to represent a single command */
typedef struct command_s {
    char **args;
    int arg_count;
    char *in_file;    /* For input redirection (<) */
    char *out_file;   /* For output redirection (>) */
    bool append;      /* For >> redirection */
    bool heredoc;     /* For << redirection */
    bool piped;       /* If command pipes to next command */
} command_t;

/* Linked list of commands */
typedef struct command_list_s {
    command_t *cmd;
    struct command_list_s *next;
} command_list_t;

/* Parsing functions */
token_list_t *parse_command_line(char *input);
void free_token_list(token_list_t *head);
command_list_t *build_command_list(token_list_t *tokens);
void free_command_list(command_list_t *head);
command_t *create_command(void);
void free_command(command_t *cmd);
void handle_operator(char *input, int *i, int *start,
    token_list_t **head);
void handle_space(char *input, int *i_start[2], char *buffer,
    token_list_t **head);
void handle_word(char *input, int *i, int *start, token_list_t **head);
void tokenize_input(char *input, token_list_t **head);
void add_token(token_list_t **head, char *token, token_type_t type);
bool is_space(char c);
bool is_operator(char c);

/* Command execution functions */
int execute_command_line(shell_state_t *shell, char *input);
int execute_commands(shell_state_t *shell, command_list_t *cmd_list);
int execute_simple_command(shell_state_t *shell, command_t *cmd);

void handle_parent_pipes(int *prev_pipe, int *pipefd, bool is_last);
void create_pipe_and_fork(int *pipefd, pid_t *pid, bool is_last);
int wait_for_pipe_children(pid_t *pids, int cmd_count);
int execute_piped_commands(shell_state_t *shell, command_list_t *cmd_list);

int check_and_execute_builtin(shell_state_t *shell, command_t *cmd);

/* Redirection handling */
int setup_redirections(command_t *cmd, int *stdin_copy, int *stdout_copy);
int reset_redirections(int stdin_copy, int stdout_copy);
int handle_heredoc(char *delimiter);
void redirection_exit(char *file, int fd, int std);

#endif
