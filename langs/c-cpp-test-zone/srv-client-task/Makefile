CC=g++
CPPFLAGS=-Wall

build: main

run:
	./main

main: server.o device.o main.o

server.o: server.cpp

device.o: device.cpp

main.o: main.cpp

clean:
	rm -rf *.o *.so *.a main
