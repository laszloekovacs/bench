UNAME_S := $(shell uname -s)

CC = gcc
# -MMD: Generate dependency files
# -MP:  Adds dummy targets to prevent errors if a header is deleted
CFLAGS = -Wall -Wextra -O2 -MMD -MP
LDFLAGS = 

ifeq ($(UNAME_S), Linux)
    LIBS = -lX11 -lGL -lrt
endif

ifeq ($(UNAME_S), FreeBSD)
    CFLAGS += -I/usr/local/include
    LDFLAGS += -L/usr/local/lib
    LIBS = -lX11 -lGL
endif

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/app

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
# Track the generated dependency files
DEPS = $(OBJ:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Compiling step: The dependency files are generated here automatically
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Include the generated dependency rules
-include $(DEPS)

.PHONY: all clean