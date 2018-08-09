CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
EXEC=main
DEPS=geohash.h Coord.h

all: $(EXEC)

main: main.o geohash.o 
	$(CC) -o main main.o geohash.o

main.o: main.c $(DEPS)
	$(CC) -o main.o -c main.c $(CFLAGS)

geohash.o: geohash.c $(DEPS)
	$(CC) -o geohash.o -c geohash.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper:
	rm -rf $(EXEC)
