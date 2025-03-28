/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Pipe handling for commands
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>

#include "my.h"
#include "error.h"
#include "minishell.h"
#include "minishell2.h"

static void setup_pipe_child(int prev_pipe, int pipefd[2], bool is_first,
    bool is_last)
{
    if (!is_first) {
        if (dup2(prev_pipe, STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(prev_pipe);
    }
    if (!is_last) {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        close(pipefd[1]);
    }
}

static void setup_first_redirection(command_t *cmd)
{
    int fd = -1;

    if (cmd->in_file) {
        if (cmd->heredoc)
            fd = handle_heredoc(cmd->in_file);
        else
            fd = open(cmd->in_file, O_RDONLY);
        redirection_exit(cmd->in_file, fd, STDIN_FILENO);
    }
}

static void setup_last_redirection(command_t *cmd)
{
    int fd = -1;

    if (cmd->out_file) {
        if (cmd->append)
            fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        redirection_exit(cmd->out_file, fd, STDOUT_FILENO);
    }
}

static void setup_pipe_redirections(command_t *cmd, bool is_first,
    bool is_last)
{
    if (is_first)
        setup_first_redirection(cmd);
    if (is_last)
        setup_last_redirection(cmd);
}

static void execute_pipe_command(shell_state_t *shell, command_t *cmd)
{
    char *cmd_path = NULL;
    int builtin_result = check_and_execute_builtin(shell, cmd);

    if (builtin_result != -1)
        exit(builtin_result);
    cmd_path = get_command_path(shell, cmd->args);
    if (cmd_path) {
        execve(cmd_path, cmd->args,
            convert_env_list_to_array(shell->env_list));
        free(cmd_path);
        perror(cmd->args[0]);
        exit(errno == ENOENT ? 127 : 1);
    } else {
        print_error(cmd->args[0], 1);
        print_error(": Command not found.\n", 1);
        exit(127);
    }
}

static int count_piped_commands(command_list_t *cmd_list)
{
    int count = 0;
    command_list_t *current = cmd_list;

    while (current != NULL) {
        count++;
        if (!current->cmd->piped && current != cmd_list)
            break;
        current = current->next;
    }
    return count;
}

static command_t *find_cd_in_pipeline(command_list_t *cmd_list, int cmd_count)
{
    command_list_t *current = cmd_list;
    int count = 0;

    while (current != NULL && count < cmd_count) {
        if (current->cmd->args && current->cmd->args[0] &&
                my_strcmp(current->cmd->args[0], "cd") == 0)
            return current->cmd;
        current = current->next;
        count++;
    }
    return NULL;
}

static void handle_pipe_child(shell_state_t *shell, command_list_t *current,
    int prev_pipefd[3], bool first_last[2])
{
    int pipefd[2] = {prev_pipefd[1], prev_pipefd[2]};
    int prev_pipe = prev_pipefd[0];
    bool is_first = first_last[0];
    bool is_last = first_last[1];

    setup_pipe_child(prev_pipe, pipefd, is_first, is_last);
    setup_pipe_redirections(current->cmd, is_first, is_last);
    execute_pipe_command(shell, current->cmd);
}

static int finish_pipe_execution(pid_t *pids, int cmd_count,
    command_list_t *cmd_list, shell_state_t *shell)
{
    command_t *cd_cmd = find_cd_in_pipeline(cmd_list, cmd_count);
    int result = wait_for_pipe_children(pids, cmd_count);

    if (cd_cmd)
        result = my_cd(shell, cd_cmd->args);
    return result;
}

int execute_piped_commands(shell_state_t *shell, command_list_t *cmd_list)
{
    int pipefd[2];
    int prev = -1;
    pid_t pids[64];
    int cmd_count = count_piped_commands(cmd_list);
    command_list_t *current = cmd_list;
    bool first_last[2] = {true, false};

    for (int i = 0; i < cmd_count; i++) {
        first_last[1] = (i == cmd_count - 1);
        create_pipe_and_fork(pipefd, &pids[i], first_last[1]);
        if (pids[i] == 0)
            handle_pipe_child(shell, current,
                (int[3]){prev, pipefd[0], pipefd[1]}, first_last);
        handle_parent_pipes(&prev, pipefd, first_last[1]);
        first_last[0] = false;
        current = current->next;
    }
    if (prev != -1)
        close(prev);
    return finish_pipe_execution(pids, cmd_count, cmd_list, shell);
}
