# Makefile para el compilador mini -> C

# Compiladores y flags
CC = gcc
CFLAGS = -Wall -Wextra -g
FLEX = flex
BISON = bison
BISON_FLAGS = -d

# Directorios
SRC_DIR = .
BUILD_DIR = build

# Archivos fuente y objetos
SRCS = main.c semantic.c symbol.c scanner.c parser.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
TARGET = mini_compiler

# Reglas principales
.PHONY: all clean run dirs

all: dirs $(TARGET)

dirs:
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Generación de scanner y parser
scanner.c scanner.h: scanner.l parser.h
	$(FLEX) --header-file=scanner.h -o scanner.c $<

parser.c parser.h: parser.y
	$(BISON) $(BISON_FLAGS) -o parser.c $<

# Compilación de objetos
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencias específicas
$(BUILD_DIR)/main.o: main.c parser.h semantic.h symbol.h
$(BUILD_DIR)/semantic.o: semantic.c semantic.h symbol.h
$(BUILD_DIR)/symbol.o: symbol.c symbol.h
$(BUILD_DIR)/scanner.o: scanner.c scanner.h parser.h
$(BUILD_DIR)/parser.o: parser.c parser.h

clean:
	rm -rf $(BUILD_DIR) $(TARGET) scanner.c scanner.h parser.c parser.h

run: $(TARGET)
	./$(TARGET) < entradaerr.txt
