# 🐚 Minishell

A lightweight Unix shell implementation written in C, recreating the core functionality of bash. This project is part of the 42 School curriculum and demonstrates deep understanding of process management, file descriptors, and Unix system calls.

## 👥 Authors

- **jkubaev** - [GitHub Profile](https://github.com/jkubaev)
- **yingzhan** - [GitHub Profile](https://github.com/yingzhan)

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Technical Implementation](#technical-implementation)
- [Project Structure](#project-structure)

## 🎯 About

Minishell is a simplified shell that mimics the behavior of bash. It provides an interactive command-line interface where users can execute commands, manage processes, handle redirections, and use pipes. The project focuses on understanding how shells work at a low level, including process creation, signal handling, and file descriptor manipulation.

## ✨ Features

### Core Functionality
- **Interactive prompt** with command history (using readline library)
- **Command execution** with PATH resolution
- **Pipe support** (`|`) for chaining multiple commands
- **Redirections**:
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Append mode (`>>`)
  - Here-document (`<<`)
- **Environment variable expansion** (`$VAR`, `$?`)
- **Quote handling** (single `'` and double `"` quotes)
- **Signal handling**:
  - `Ctrl+C` - Interrupt current command
  - `Ctrl+D` - Exit shell
  - `Ctrl+\` - Quit (ignored in interactive mode)

### Built-in Commands
- `echo` (with `-n` option)
- `cd` (with relative or absolute path)
- `pwd` (print working directory)
- `export` (set environment variables)
- `unset` (remove environment variables)
- `env` (display environment variables)
- `exit` (exit the shell with optional exit code)

## 🚀 Installation

### Prerequisites
- GCC compiler
- GNU Make
- readline library

On Ubuntu/Debian:
```bash
sudo apt-get install build-essential libreadline-dev
```

On macOS:
```bash
brew install readline
```

### Build
```bash
# Clone the repository
git clone [your-repo-url]
cd minishell

# Compile the project
make

# Run minishell
./minishell
```

### Clean
```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild from scratch
```

## 💻 Usage

### Basic Commands
```bash
minishell$ ls -la
minishell$ echo "Hello, World!"
minishell$ pwd
```

### Pipes
```bash
minishell$ ls -l | grep minishell | wc -l
minishell$ cat file.txt | grep pattern | sort
```

### Redirections
```bash
minishell$ echo "Hello" > output.txt
minishell$ cat < input.txt
minishell$ ls >> log.txt
minishell$ cat << EOF
> line 1
> line 2
> EOF
```

### Environment Variables
```bash
minishell$ echo $PATH
minishell$ export MY_VAR=value
minishell$ echo $MY_VAR
minishell$ echo $?  # Print last exit code
```

### Quotes
```bash
minishell$ echo "Hello $USER"     # Variable expansion
minishell$ echo 'Hello $USER'     # Literal string
```

## 🔧 Built-in Commands

| Command | Description | Example |
|---------|-------------|---------|
| `echo` | Print arguments to stdout | `echo -n "Hello"` |
| `cd` | Change directory | `cd /home/user` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variable | `export VAR=value` |
| `unset` | Remove environment variable | `unset VAR` |
| `env` | Display environment | `env` |
| `exit` | Exit the shell | `exit 0` |

## 🏗️ Technical Implementation

### Architecture

The project follows a modular architecture with clear separation of concerns:

1. **Tokenization** - Breaks input into tokens (words, operators, quotes)
2. **Parsing** - Builds an Abstract Syntax Tree (AST) from tokens
3. **Execution** - Traverses the AST and executes commands

### Key Components

#### Tokenizer
- Handles quotes (single and double)
- Recognizes operators (pipes, redirections)
- Expands environment variables
- Splits input into meaningful tokens

#### Parser
- Creates AST nodes for commands, pipes, and redirections
- Validates syntax
- Handles operator precedence

#### Executor
- Manages process creation with `fork()`
- Sets up pipes and redirections
- Handles built-in commands
- Manages file descriptors

#### Signal Handler
- Custom signal handling for interactive mode
- Different behavior during command execution
- Proper cleanup on interrupts

### Data Structures

```c
// Main shell structure
typedef struct s_shell {
    t_env   *env_list;      // Environment variables
    t_node  *nodes;         // AST root
    char    *input;         // Current input
    int     exit_code;      // Last exit code
} t_shell;

// AST node types
typedef enum e_node_type {
    COMMAND,    // Simple command
    PIPE,       // Pipe operator
    REDIR,      // Redirection
} t_node_type;
```

## 📁 Project Structure

```
minishell/
├── includes/           # Header files
│   ├── minishell.h    # Main header
│   ├── execution.h    # Execution functions
│   ├── parsing.h      # Parser functions
│   ├── tokenizing.h   # Tokenizer functions
│   └── type.h         # Type definitions
├── tokenizing/        # Tokenization logic
├── parsing/           # Parser implementation
├── exec/              # Execution engine
│   ├── built_ins/    # Built-in commands
│   └── non_builtin/  # External command execution
├── heredoc/          # Here-document handling
├── signals/          # Signal management
├── env/              # Environment variable handling
├── libft/            # Custom C library
├── main.c            # Entry point
└── Makefile          # Build configuration
```

## 🎓 Learning Outcomes

This project provides hands-on experience with:
- Unix process management (`fork`, `execve`, `wait`)
- File descriptor manipulation and redirection
- Signal handling in C
- Memory management and leak prevention
- Parsing and AST construction
- System calls and error handling
- Collaborative development with Git

## 📝 Notes

- Exit codes follow bash conventions (0-255)
- Unclosed quotes result in syntax errors
- The shell handles `$?` to display the last exit code
- Memory leaks are carefully managed throughout the codebase
- Signal handling differs between interactive and execution modes

## 🐛 Known Limitations

- No support for logical operators (`&&`, `||`)
- No wildcard expansion (`*`)
- No command substitution (`` `command` `` or `$(command)`)
- No job control (`bg`, `fg`, `jobs`)
- Limited to single-line commands

## 📄 License

This project is part of the 42 School curriculum.

---

*Built with ❤️ as part of the 42 Berlin curriculum*
