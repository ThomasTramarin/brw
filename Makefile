CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g -I$(SRC_DIR)

SRC_DIR = src
BUILD_DIR = build

BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = $(BIN_DIR)/brw

all: directories $(TARGET)

directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean directories all

clean:
	rm -rf $(BUILD_DIR)