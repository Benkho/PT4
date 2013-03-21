CC=gcc
CFLAGS=-Wall -lm
LDFLAGS=
EXEC=taar

all: $(EXEC)

taar: main.o functions.o
	$(CC) -o $(EXEC) main.o functions.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(LDFLAGS)

functions.o: functions.c
	$(CC) -c functions.c $(LDFLAGS)


clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
