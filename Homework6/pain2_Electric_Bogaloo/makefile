CC = gcc
CFLAGS = -Wall
TARGET = driver
SRC_DIR = src
OBJ_DIR = obj
SRCS = list.c driver.c
OBJS = list.o driver.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean