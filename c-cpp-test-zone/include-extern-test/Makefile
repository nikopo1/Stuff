CC=gcc
CFLAGS=-g -Wall

main: file_a.o file_b.o
	$(CC) $(CFLAGS) $^ -o $@

file_a.o: file_a.c

file_b.o: file_b.c

clean:
	rm -rf *.o main
