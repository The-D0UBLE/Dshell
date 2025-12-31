# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude

# Source files
SRC = src/main.c \
      src/loop.c \
      src/banner.c \
      src/input.c \
      src/parser.c \
      src/execute.c \
      src/builtins.c

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = dshell

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Mark 'all' and 'clean' as phony targets
.PHONY: all clean

