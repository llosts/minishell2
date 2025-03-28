/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Input/output redirection handling
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "my.h"
#include "error.h"
#include "minishell.h"
#include "minishell2.h"

static int helper_redirection(int *stdin_copy, int fd_in, int std)
{
    if (*stdin_copy == -1) {
        close(fd_in);
        perror("dup");
        return -1;
    }
    if (dup2(fd_in, std) == -1) {
        close(fd_in);
        close(*stdin_copy);
        perror("dup2");
        return -1;
    }
    return 0;
}

static int setup_input_redirection(command_t *cmd, int *stdin_copy)
{
    int fd_in = -1;

    if (cmd->in_file) {
        if (cmd->heredoc)
            fd_in = handle_heredoc(cmd->in_file);
        else
            fd_in = open(cmd->in_file, O_RDONLY);
        if (fd_in == -1) {
            perror(cmd->in_file);
            return -1;
        }
        *stdin_copy = dup(STDIN_FILENO);
        if (helper_redirection(stdin_copy, fd_in, STDIN_FILENO) == -1)
            return -1;
        close(fd_in);
    }
    return 0;
}

static int setup_output_redirection(command_t *cmd, int *stdout_copy)
{
    int fd_out = -1;

    if (cmd->out_file) {
        if (cmd->append)
            fd_out = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror(cmd->out_file);
            return -1;
        }
        *stdout_copy = dup(STDOUT_FILENO);
        if (helper_redirection(stdout_copy, fd_out, STDOUT_FILENO) == -1)
            return -1;
        close(fd_out);
    }
    return 0;
}

static void helper_heredoc_input(int pipefd[2], char *delimiter)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        if (my_strncmp(line, delimiter, my_strlen(delimiter)) == 0 &&
            (line[my_strlen(delimiter)] == '\n' ||
            line[my_strlen(delimiter)] == '\0'))
            break;
        write(pipefd[1], line, my_strlen(line));
        if (isatty(STDIN_FILENO))
            my_putstr("? ");
    }
    free(line);
}

int handle_heredoc(char *delimiter)
{
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    if (isatty(STDIN_FILENO))
        my_putstr("? ");
    helper_heredoc_input(pipefd, delimiter);
    close(pipefd[1]);
    return pipefd[0];
}

int setup_redirections(command_t *cmd, int *stdin_copy, int *stdout_copy)
{
    *stdin_copy = -1;
    *stdout_copy = -1;
    if (setup_input_redirection(cmd, stdin_copy) == -1)
        return -1;
    if (setup_output_redirection(cmd, stdout_copy) == -1) {
        if (*stdin_copy != -1) {
            dup2(*stdin_copy, STDIN_FILENO);
            close(*stdin_copy);
        }
        return -1;
    }
    return 0;
}

int reset_redirections(int stdin_copy, int stdout_copy)
{
    if (stdin_copy > 0) {
        if (dup2(stdin_copy, STDIN_FILENO) == -1)
            perror("dup2");
        close(stdin_copy);
    }
    if (stdout_copy > 0) {
        if (dup2(stdout_copy, STDOUT_FILENO) == -1)
            perror("dup2");
        close(stdout_copy);
    }
    return 0;
}
