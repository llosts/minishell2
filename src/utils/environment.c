/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Environment variable handling utilities
*/

#include <stdlib.h>
#include <string.h>

#include "my.h"
#include "minishell.h"

env_node_t *init_env_list(char const **envp)
{
    env_node_t *head = NULL;
    char *key = NULL;
    char *value = NULL;

    for (int i = 0; envp[i] != NULL; i++) {
        key = strtok(my_strdup(envp[i]), "=");
        value = strtok(NULL, "");
        head = add_env_node(head, key, value);
        free(key);
        if (!head) {
            free_env_list(head);
            return NULL;
        }
    }
    return head;
}

env_node_t *add_env_node(env_node_t *head, const char *key, const char *value)
{
    env_node_t *new_node = malloc(sizeof(env_node_t));

    if (!new_node)
        return NULL;
    new_node->key = my_strdup(key);
    new_node->value = my_strdup(value);
    if (!new_node->key || !new_node->value) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return NULL;
    }
    new_node->next = head;
    head = new_node;
    return new_node;
}

void free_env_list(env_node_t *head)
{
    env_node_t *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

char *get_env_value(env_node_t *env_list, const char *key)
{
    while (env_list != NULL) {
        if (my_strcmp(env_list->key, key) == 0)
            return env_list->value;
        env_list = env_list->next;
    }
    return NULL;
}

env_node_t *create_reversed_copy(env_node_t *head)
{
    env_node_t *reversed_head = NULL;
    env_node_t *new_node = NULL;

    while (head != NULL) {
        new_node = malloc(sizeof(env_node_t));
        if (!new_node)
            return NULL;
        new_node->key = my_strdup(head->key);
        new_node->value = my_strdup(head->value);
        if (!new_node->key || !new_node->value) {
            free_env_list(reversed_head);
            return NULL;
        }
        new_node->next = reversed_head;
        reversed_head = new_node;
        head = head->next;
    }
    return reversed_head;
}
