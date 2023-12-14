# Simple Shell

## Table of Contents

- [Introduction](#introduction)
- [Project Information](#project-information)
- [Documentation](#documentation)
- [Authors](#authors)

## Introduction

### What is Shell

A **shell** is a command-line interpreter, providing a user interface to access the services of an operating system. Shells can vary based on their interface types; this project focuses on developing a shell program of the type **`sh`** ([Bourne Shell](https://en.wikipedia.org/wiki/Bourne_shell)). Users interact with it via a [terminal emulator](https://en.wikipedia.org/wiki/Terminal_emulator), entering data and receiving output from the system.

### Purpose

The project aims to create a simple yet functional shell interpreter. It supports features like process control, I/O redirection, script execution, and more. This shell is compatible with Unix-type systems and is located at **`/bin/sh`** in the Unix file hierarchy.

## Project Information

### Tasks

- Task 0: README, man page, AUTHORS file.
- Task 1: Code adhering to Betty coding style.
- Task 2: Simple shell 0.1 - basic command execution.
- Task 3: Simple shell 0.2 - handle command line arguments.
- Task 4: Simple shell 0.3 - handle the PATH.
- Task 5: Simple shell 0.4 - implement exit and env built-ins.
- Task 6: Simple shell 1.0 - additional features and robustness.

### Environment

- OS: Ubuntu 20.04 LTS
- Language: C
- Compiler: gcc 9.3.0
- Editor: VIM 8.1.2269
- Version Control: Git
- Style Guidelines: [Betty style](https://github.com/holbertonschool/Betty/wiki)

### General Requirements

- Allowed editors: vi, vim, emacs.
- Files compiled on Ubuntu 14.04 LTS.
- C programs and functions compiled with gcc 4.8.4 using flags `-Wall -Werror -Wextra -pedantic`.
- Code must follow Betty style.
- Limit of 5 functions per file.
- All header files should be include guarded.
- No memory leaks.
- Program output should match `sh` (`/bin/sh`) exactly.

### Allowed Functions

- `execve`, `exit`, `_exit`, `fork`, `free`, `getline`, `isatty`, `malloc`, `perror`, `signal`, `stat` (__xstat), `strtok`, `wait`, `write`.

## Documentation

### Installation

- Clone the repository: `git clone [repository URL]`.
- Navigate to the repository: `cd [repository directory]`.
- Compile: `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`.
- Run interactively: `./hsh`.
- Run non-interactively: `echo "[command]" | ./hsh`.

### Testing

(Provide instructions for testing the shell, including running any test scripts provided in the repository.)

### Files

- `shell.c`: Main shell program.
- `execute.c`: Executes commands.
- `getenv.c`: Retrieves environment variables.
- `getline_command.c`: Handles input lines.
- `get_path.c`: Manages the PATH environment variable.
- `shell.h`: Header file with function prototypes and definitions.
- `str_utils.c`: String utility functions.
- `values_path.c`: Processes path values.




## Authors

Geraldo Irizarry Martel
Norman Colon

---

This `README.md` provides a comprehensive overview of your project, including its purpose, technical details, and how to use it. Make sure to replace placeholders like `[repository URL]` with actual information relevant to your project.

