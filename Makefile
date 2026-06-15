CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O0 -g -Iinclude

SRC_DIR = .
BIN_DIR = bin

SRCS = $(SRC_DIR)/main.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

TARGET = $(BIN_DIR)/program

all: $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

test: $(BIN_DIR)/test.o $(filter-out $(BIN_DIR)/main.o,$(OBJS))
	$(CC) $(CFLAGS) $(filter-out $(BIN_DIR)/main.o,$(OBJS)) $(BIN_DIR)/test.o -o $(BIN_DIR)/test_exec
	./$(BIN_DIR)/test_exec

$(BIN_DIR)/test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o $(BIN_DIR)/test.o

clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)
	rm -f $(BIN_DIR)/*.o

run: all
	./$(TARGET)