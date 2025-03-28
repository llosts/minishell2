/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Process execution and command path resolution
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my.h"
#include "error.h"
#include "minishell.h"

static char *create_full_path(const char *directory, const char *command)
{
    char *full_path = malloc(my_strlen(directory) + my_strlen(command) + 2);

    if (!full_path)
        return NULL;
    my_strcpy(full_path, directory);
    my_strcat(full_path, "/");
    my_strcat(full_path, command);
    return full_path;
}

static void print_coredump(int status)
{
    if (WCOREDUMP(status))
        print_error(" (core dumped)\n", 0);
    else
        print_error("\n", 0);
}

static void handle_exec_error(char *cmd_path, char **args)
{
    if (errno == ENOEXEC) {
        print_error(args[0], 1);
        print_error(": Exec format error. Binary file not executable.\n", 1);
        exit(1);
    }
    if (errno == ENOENT) {
        print_error(args[0], 1);
        print_error(": No such file or directory.\n", 1);
        exit(127);
    }
    if (errno == EACCES) {
        print_error(args[0], 1);
        print_error(": Permission denied.\n", 1);
        exit(1);
    }
    free(cmd_path);
    exit(127);
}

static char *find_command_in_path(shell_state_t *shell, const char *command)
{
    char *path = get_env_value(shell->env_list, "PATH");
    char **paths = my_str_to_word_array(path, ":");
    char *full_path = NULL;

    if (!path || !paths)
        return NULL;
    for (int i = 0; paths[i]; i++) {
        full_path = create_full_path(paths[i], command);
        if (!full_path)
            continue;
        if (access(full_path, X_OK) == 0) {
            free_array(paths);
            return full_path;
        }
        free(full_path);
    }
    free_array(paths);
    return NULL;
}

int handle_exit_status(int status)
{
    int signal = 0;

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        signal = WTERMSIG(status);
        if (signal == SIGSEGV) {
            print_error("Segmentation fault", 0);
            print_coredump(status);
        }
        if (signal == SIGFPE) {
            print_error("Floating point exception", 0);
            print_coredump(status);
        }
        return 128 + signal;
    }
    return FAILURE;
}

char *get_command_path(shell_state_t *shell, char **args)
{
    if (!args[0])
        return NULL;
    if (my_strchr(args[0], '/')) {
        if (access(args[0], X_OK) == 0)
            return my_strdup(args[0]);
    } else
        return find_command_in_path(shell, args[0]);
    return NULL;
}

void execute_child_process(char *cmd_path, char **args, shell_state_t *shell)
{
    execve(cmd_path, args, convert_env_list_to_array(shell->env_list));
    handle_exec_error(cmd_path, args);
}

int fork_and_execute(char *cmd_path, char **args, shell_state_t *shell)
{
    pid_t pid = fork();
    int status = 0;

    if (pid < 0) {
        perror("fork");
        free(cmd_path);
        return FAILURE;
    }
    if (pid == 0) {
        execute_child_process(cmd_path, args, shell);
    } else {
        waitpid(pid, &status, 0);
        free(cmd_path);
        return handle_exit_status(status);
    }
    return SUCCESS;
}

int execute_single_command(shell_state_t *shell, char **args)
{
    char *cmd_path = get_command_path(shell, args);

    if (!cmd_path) {
        print_error(args[0], 1);
        return print_error(": Command not found.\n", 1);
    }
    if (access(cmd_path, X_OK) != 0) {
        perror(args[0]);
        free(cmd_path);
        return (errno == EACCES) ? 126 : 127;
    }
    return fork_and_execute(cmd_path, args, shell);
}
