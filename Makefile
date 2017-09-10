CC = gcc
CFLAGS = -I. -Wall
DEPS = *.h
objects = symbol.o symbolList.o symbolTable.o

%.o: %.c $(DEPS)
	$(CC) -c $< $(CFLAGS)

main.out: $(objects) main.o
	gcc -o main.out $(objects) main.o $(CFLAGS)

clean:
	rm $(objects) main.o*
