CC = gcc -std=c++17

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Base Flags
BASE_CFLAGS = -Wall -Wextra -g -I$(INC_DIR)
BASE_LDFLAGS =

# Platform-Specific Flags
DARWIN_CFLAGS = $(BASE_CFLAGS)
DARWIN_LDFLAGS = $(BASE_LDFLAGS) -lc++ -lc++abi

LINUX_CFLAGS = $(BASE_CFLAGS)
LINUX_LDFLAGS = $(BASE_LDFLAGS) -lstdc++

SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

NAME = BlockParser


all: darwin

# General rule to compile any object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile for Darwin (macOS)
darwin: CFLAGS = $(DARWIN_CFLAGS)
darwin: LDFLAGS = $(DARWIN_LDFLAGS)
darwin: $(BIN_DIR)/$(NAME)

# Rule to compile for Linux
linux: CFLAGS = $(LINUX_CFLAGS)
linux: LDFLAGS = $(LINUX_LDFLAGS)
linux: $(BIN_DIR)/$(NAME)


$(BIN_DIR)/$(NAME): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/*

re: clean all

.PHONY: all darwin linux clean re
