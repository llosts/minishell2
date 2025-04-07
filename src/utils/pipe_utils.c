/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** pipe_utils.c
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell2.h"
#include "error.h"

void create_pipe_and_fork(int *pipefd, pid_t *pid, bool is_last)
{
    if (!is_last && pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    *pid = fork();
    if (*pid == -1) {
        perror("fork");
        exit(1);
    }
}

void handle_parent_pipes(int *prev_pipe, int *pipefd, bool is_last)
{
    if (*prev_pipe != -1)
        close(*prev_pipe);
    if (!is_last) {
        close(pipefd[1]);
        *prev_pipe = pipefd[0];
    }
}

int wait_for_pipe_children(pid_t *pids, int cmd_count)
{
    int status = 0;
    int result = 0;

    for (int i = 0; i < cmd_count; i++) {
        waitpid(pids[i], &status, 0);
        if (i == cmd_count - 1)
            result = handle_exit_status(status);
    }
    return result;
}
