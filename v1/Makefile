CC=gcc -std=gnu99
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=opp

all: $(EXEC)

opp: opp.o 
	$(CC) -o opp opp.o $(LDFLAGS)

opp.o: opp.c
	$(CC) -o opp.o -c opp.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
