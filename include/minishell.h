/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-nathan.cheynet
** File description:
** Core shell definitions and structures
*/

#ifndef MINISHELL_H_
    #define MINISHELL_H_

typedef struct env_node_s {
    char *key;
    char *value;
    struct env_node_s *next;
} env_node_t;

typedef struct shell_state_s {
    env_node_t *env_list;
    int last_exit_status;
} shell_state_t;

typedef struct builtin_s {
    char *name;
    int (*func)(shell_state_t *shell, char **args);
} builtin_t;

/* Shell initialization and main loop */
void start_minishell(shell_state_t *shell);
int handle_input(shell_state_t *shell, char *input);

/* Environment management */
env_node_t *init_env_list(char const **envp);
env_node_t *add_env_node(env_node_t *head, const char *key, const char *value);
void free_env_list(env_node_t *head);
char *get_env_value(env_node_t *env_list, const char *key);
env_node_t *create_reversed_copy(env_node_t *head);
char **convert_env_list_to_array(env_node_t *env_list);

/* Builtins */
int my_cd(shell_state_t *shell, char **args);
int my_setenv(shell_state_t *shell, char **args);
int my_unsetenv(shell_state_t *shell, char **args);
int my_env(shell_state_t *shell, char **args);

/* Path and directory handling */
char *get_target_directory(shell_state_t *shell, char **args);
int change_directory(shell_state_t *shell, const char *target);
char *expand_home(shell_state_t *shell, const char *path);

/* Command execution */
int execute_single_command(shell_state_t *shell, char **args);
char *get_command_path(shell_state_t *shell, char **args);
int handle_exit_status(int status);

/* Utils */
char **parse_input(char *input);
void free_array(char **array);
char **resize_array(char **old_array, int old_size, int new_size);

static const builtin_t builtin_handler[] = {
    {"cd", &my_cd},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"env", &my_env},
    {NULL, NULL}
};

#endif
