# Compiler & flags
CC          = gcc
CFLAGS      = -Wall -ansi -pedantic -O0 -MMD -MP
LDFLAGS     =

# ASan flags
ASAN_CFLAGS = -g -O0 -fsanitize=address -fno-omit-frame-pointer
ASAN_LDFLAGS = -fsanitize=address -static-libasan

# Valgrind flags
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -q

# Targets & directories
TARGET    = assembler
SRC_DIR   = .
OBJ_DIR   = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

# Default: Release build
all: $(TARGET)

# Build with ASan
asan: CFLAGS += $(ASAN_CFLAGS)
asan: LDFLAGS += $(ASAN_LDFLAGS)
asan: $(TARGET)

# Build (plain) then run under Valgrind
valgrind: all
	$(VALGRIND) ./$(TARGET)

# Build with ASan, then run
asan-run: asan
	./$(TARGET) ./example_with_macros

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all asan valgrind asan-run clean
