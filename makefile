CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

clean:
	rm *.o buildidx key2val val2key actors bacon1

all: buildidx key2val val2key actors bacon1

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

buildidx: buildidx.o hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) -o buildidx buildidx.o hashfn.o util.o

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

key2val: key2val.o hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) -o key2val key2val.o hashfn.o util.o

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

val2key: val2key.o hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) -o val2key val2key.o hashfn.o util.o

actors.o: actors.c
	$(CC) $(CFLAGS) -c actors.c -o actors.o

actors: actors.o hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) -o actors actors.o hashfn.o util.o

bacon1.o: bacon1.c
	$(CC) $(CFLAGS) -c bacon1.c -o bacon1.o

bacon1: bacon1.o hashfn.o util.o hashfn.h util.h
	$(CC) $(CFLAGS) -o bacon1 bacon1.o hashfn.o util.o