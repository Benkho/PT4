CC=gcc
CFLAGS=-std=c99 -lm
EXEC=taar

all: $(EXEC)

taar: taar.o 
	$(CC) -o taar taar.o

taar.o: taar.c
	$(CC) -o taar.o -c taar.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
