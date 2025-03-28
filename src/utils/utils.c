/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Utility functions for string and array handling
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "my.h"
#include "error.h"
#include "minishell.h"

static int count_list(env_node_t *head)
{
    int count = 0;

    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

char **resize_array(char **old_array, int old_size, int new_size)
{
    char **new_array = malloc(new_size * sizeof(char *));

    if (!new_array) {
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        exit(FAILURE);
    }
    for (int i = 0; i < old_size; i++)
        new_array[i] = old_array[i];
    free(old_array);
    return new_array;
}

char **parse_input(char *input)
{
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token = NULL;

    if (!tokens)
        return NULL;
    token = strtok(input, " \t\n");
    while (token != NULL) {
        tokens[position] = my_strdup(token);
        position += 1;
        if (position >= bufsize) {
            bufsize += 64;
            tokens = resize_array(tokens, position, bufsize);
        }
        token = strtok(NULL, " \t\n");
    }
    tokens[position] = NULL;
    return tokens;
}

char **convert_env_list_to_array(env_node_t *env_list)
{
    env_node_t *current = env_list;
    int count = count_list(current);
    char **env_array = malloc(sizeof(char *) * (count + 1));
    int len = 0;

    if (!env_array)
        return NULL;
    current = env_list;
    for (int i = 0; i < count; i++) {
        len = my_strlen(current->key) + my_strlen(current->value) + 2;
        env_array[i] = malloc(len);
        if (!env_array[i])
            return NULL;
        my_strcpy(env_array[i], current->key);
        my_strcat(env_array[i], "=");
        my_strcat(env_array[i], current->value);
        current = current->next;
    }
    env_array[count] = NULL;
    return env_array;
}

void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void redirection_exit(char *file, int fd, int std)
{
    if (fd != -1) {
        if (dup2(fd, std) == -1) {
            perror("dup2");
            exit(1);
        }
        close(fd);
    } else {
        perror(file);
        exit(1);
    }
}
