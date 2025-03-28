# Minishell2

## Overview
Minishell2 is a command-line interpreter that implements basic shell functionality. This project extends the capabilities of minishell1 by adding support for:

- Command separators (`;`)
- Pipes (`|`) for connecting command outputs to inputs
- Input and output redirections (`<`, `>`, `>>`, `<<`)

## Features

### Basic Shell Features
- Command execution
- Builtin commands: `cd`, `setenv`, `unsetenv`, `env`
- Path resolution
- Environment variable management

### Advanced Features
- **Command separators**: Run multiple commands in sequence (e.g., `ls -l; pwd`)
- **Pipes**: Connect the output of one command to the input of another (e.g., `ls | wc -l`)
- **Redirections**:
  - `>`: Redirect output to a file (overwrite mode)
  - `>>`: Redirect output to a file (append mode)
  - `<`: Use file as input
  - `<<`: Here document functionality

## Compilation
The project includes a Makefile with the following rules:

```
make            # Compile the program
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Recompile the program
make debug      # Compile with debug flags
make bonus      # Compile with the bonus features
```

## Usage
After compilation, run the shell:

```
./mysh
```

You will be greeted with a prompt:

```
$>
```

You can now enter commands:

```
$> ls -l
$> cat file.txt
$> ls -l | grep ".c" | wc -l
$> echo "Hello" > output.txt
$> cat < input.txt
```

To exit the shell, use the `exit` command or press Ctrl+D.

## Project Structure
```
.
├── include/                # Header files
│   ├── error.h            # Error handling definitions
│   ├── minishell.h        # Core shell structures and declarations
│   └── minishell2.h       # Extended shell functionality declarations
├── lib/                    # Libraries
│   └── my/                # Custom C library
├── src/                    # Source files
│   ├── builtins/          # Built-in command implementations
│   │   ├── builtins.c     # env, setenv, unsetenv implementations
│   │   └── my_cd.c        # cd command implementation
│   ├── commands/          # Command execution
│   │   ├── commands.c     # Command execution logic
│   │   ├── executor.c     # Process execution handling
│   │   ├── pipes.c        # Pipe handling
│   │   └── redirects.c    # Redirection handling
│   ├── parser/            # Input parsing
│   │   ├── memory.c       # Memory management for parser structures
│   │   ├── parser.c       # Command line parsing
│   │   └── token.c        # Token processing
│   ├── utils/             # Utility functions
│   │   ├── environment.c  # Environment variable handling
│   │   ├── parser_utils.c # Parsing helper functions
│   │   ├── pipe_utils.c   # Pipe-related utilities
│   │   ├── usage.c        # Help and usage information
│   │   └── utils.c        # General utilities
│   ├── main.c             # Program entry point
│   └── shell.c            # Main shell loop
├── bonus/                  # Bonus implementations
├── Makefile                # Compilation rules
└── README.md               # This file
```

## Error Handling
The shell handles various error conditions:
- Command not found
- Permission denied
- Invalid redirection syntax
- Pipe errors
- Invalid null commands in pipes

## Limitations
- No wildcard expansion
- No command history
- No variable expansion (except for environment variables)
- No arithmetic expansion

## License
This project was created as part of the Epitech curriculum.

---

© 2025 Nathan Cheynet - Epitech Project
