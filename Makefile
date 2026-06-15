CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O0 -g -Iinclude

SRC_DIR = .
BIN_DIR = bin

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/session.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

TARGET = $(BIN_DIR)/program

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	if exist $(BIN_DIR) del /Q $(BIN_DIR)\*.o $(TARGET).exe 2>nul

run: all
	./$(TARGET).exe

