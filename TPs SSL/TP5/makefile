all: programa

programa: main.o parser.o scanner.o
	gcc -o programa main.o parser.o scanner.o

main.o: main.c parser.h scanner.h
	gcc -c main.c -o main.o

parser.c parser.h: parser.y
	bison -d parser.y -o parser.c

scanner.c scanner.h: scanner.l
	flex -o scanner.c scanner.l

parser.o: parser.c parser.h
	gcc -c parser.c -o parser.o

scanner.o: scanner.c scanner.h
	gcc -c scanner.c -o scanner.o

clean:
	del *.o programa parser.c parser.h scanner.c
