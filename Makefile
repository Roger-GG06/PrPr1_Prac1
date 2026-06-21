CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O0 -g -Iinclude

SRCS = main.c session.c utils.c utilsFun.c eines.c tasques.c piece.c
TARGET = programa
TEST_TARGET = tests

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): test.c session.c utils.c utilsFun.c tasques.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET)

