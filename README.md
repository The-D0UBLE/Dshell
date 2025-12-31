# Dshell

**Dshell** is a lightweight, educational shell written in C, inspired by Stephen Brennan’s LSH tutorial. It allows you to execute Unix commands, as well as custom built-in commands defined by the user. It supports multi-file organization, a custom ASCII banner, and an easy mechanism to add your own commands.

---

## Table of Contents

1. [Features](#features)  
2. [Project Structure](#project-structure)  
3. [Building Dshell](#building-dshell)  
4. [Running Dshell](#running-dshell)  
5. [How it Works](#how-it-works)  
   - [Reading Input](#reading-input)  
   - [Parsing Commands](#parsing-commands)  
   - [Executing Commands](#executing-commands)  
   - [Built-in Commands](#built-in-commands)  
6. [Adding Your Own Custom Commands](#adding-your-own-custom-commands)  
7. [Sample Custom Commands Template](#sample-custom-commands-template)  
8. [Future Enhancements](#future-enhancements)  

---

## Features

- Modular multi-file C project
- Reads user input dynamically (supports long lines)
- Splits input into tokens (command + arguments)
- Executes both built-in commands and external system commands
- Custom ASCII banner at startup
- Easy to add your own built-in commands
- Minimal dependencies — only standard C library

---

## Project Structure

```
dshell/
├── include/
│   ├── dshell.h       # Core function declarations
│   └── builtins.h     # Built-in command declarations
├── src/
│   ├── main.c         # Program entry point
│   ├── loop.c         # Main shell loop
│   ├── banner.c       # ASCII banner
│   ├── input.c        # Input reading
│   ├── parser.c       # Tokenizing input
│   ├── execute.c      # Executing commands
│   └── builtins.c     # Built-in command implementations
├── Makefile           # Build automation
└── README.md
```

---

## Building Dshell

### Using Makefile

From the project root:

```bash
make
```

This will produce an executable named `dshell`.  

To clean up:

```bash
make clean
```

### Using GCC manually

```bash
gcc -Wall -Wextra -Wpedantic -Iinclude src/*.c -o dshell
```

---

## Running Dshell

```bash
./dshell
```

You will see a custom ASCII banner, then a prompt:

```
=================================
   ____  _____ _          _ _  
  |  _ \ ___| |__   ___| | |
  | | | / __| '_ \ / _ \ | |
  | |_| \__ \ | | |  __/ | |
  |____/|___/_| |_|\___|_|_|
=================================
          Dshell v0.1
 dshell>
```

Type commands at the prompt. Examples:

```bash
dshell> ls -l
dshell> cd /tmp
dshell> dsay
```

---

## How it Works

Dshell’s operation can be broken down into four main steps:

### 1. Reading Input

- Function: `dshell_read_line()`
- Reads a full line from `stdin`, dynamically expanding memory if the line is too long.
- Returns a `char*` containing the raw input string.

### 2. Parsing Commands

- Function: `dshell_split_line(char *line)`
- Splits the input string into tokens (command + arguments) using delimiters like space, tab, or newline.
- Returns a `char **args` — a NULL-terminated array of strings.

Example:

```bash
input: "ls -l /home"
args[0] = "ls"
args[1] = "-l"
args[2] = "/home"
args[3] = NULL
```

### 3. Executing Commands

- Function: `dshell_execute(char **args)`
- Checks if the first token matches a built-in command:
  - If yes → calls the corresponding built-in function
  - If no → forks a child process and executes an external command using `execvp`
- Waits for the child process to finish before returning control.

### 4. Built-in Commands

- Stored in `builtins.c`
- Currently includes:
  - `cd <dir>` → change directory
  - `help` → prints available commands
  - `exit` → exits the shell
  - `dsay` → prints a custom message
- Built-ins share the same signature:

```c
int builtin_name(char **args);
```

- Each built-in receives the full argument array (`args`), even if it doesn’t use all of them.

---

## Adding Your Own Custom Commands

Adding a new command is simple:

### Step 1: Write the function in `builtins.c`

```c
int dshell_greet(char **args)
{
    (void)args; // ignore args if unused
    printf("Hello from Dshell!\n");
    return 1; // return 1 to keep shell running
}
```

### Step 2: Register it

1. Add the command name to `builtin_str[]`:

```c
char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "dsay",
    "greet"   // new command
};
```

2. Add the function pointer to `builtin_func[]`:

```c
int (*builtin_func[])(char **) = {
    dshell_cd,
    dshell_help,
    dshell_exit,
    dshell_dsay,
    dshell_greet
};
```

3. Recompile:

```bash
make clean
make
./dshell
```

Now you can run:

```bash
dshell> greet
Hello from Dshell!
```

**Notes:**

- All built-in functions must return `1` to keep the shell running, or `0` to exit.
- Use `(void)args;` if your function does not need arguments to avoid compiler warnings.

---

## Sample Custom Commands Template

Here are some ready-to-use built-in command examples you can add:

```c
int dshell_dsay(char **args) {
    (void)args;
    printf("Dshell says hello!\n");
    return 1;
}

int dshell_time(char **args) {
    (void)args;
    time_t t = time(NULL);
    printf("Current time: %s", ctime(&t));
    return 1;
}

int dshell_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
    return 1;
}
```

Register them in `builtin_str[]` and `builtin_func[]` as shown previously.

---

## Future Enhancements

- **Command Whitelist:** restrict which external programs can run
- **Prompt customization:** add colors or display current directory
- **History support:** store previous commands and enable arrow navigation
- **Pipes & redirection:** support `|`, `>`, `<`
- **Scripting:** allow batch commands from a file
- **Config file (`.dshellrc`)**: load default commands or aliases at startup

---

## Summary

Dshell is a modular, customizable shell that:

- Demonstrates multi-file C projects
- Teaches dynamic input handling
- Uses function pointers for built-in commands
- Provides a simple framework to add your own commands

It’s perfect for experimentation, learning, or building a **custom restricted shell**.

