CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pendatic-errors
TARGET = programa

all: $(TARGET)

# construir el ejecutable
$(TARGET): main.o tabla.o conversion.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o tabla.o conversion.o

# construir los archivos objeto
main.o: main.c tabla.h
	$(CC) $(CFLAGS) -c main.c

tabla.o: tabla.c tabla.h conversion.h
	$(CC) $(CFLAGS) -c tabla.c

conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) -c conversion.c

# limpiar los archivos generados
clean:
	rm -f *.o $(TARGET)

# ejecutar el programa
run: programa
	./programa
