CC = gcc
FLAGS = -Wall -O3 -Iinclude/

all: bin main.o client.o list.o queue.o
	$(CC) $(FLAGS) obj/main.o obj/client.o obj/list.o obj/queue.o -lncurses -o bin/a.out

main.o: src/main.c
	$(CC) $(FLAGS) -c src/main.c -o obj/main.o

client.o: src/client.c include/client.h
	$(CC) $(FLAGS) -c src/client.c -o obj/client.o

list.o: src/list.c include/list.h
	$(CC) $(FLAGS) -c src/list.c -o obj/list.o

queue.o: src/queue.c include/queue.h
	$(CC) $(FLAGS) -c src/queue.c -o obj/queue.o

bin:
	mkdir bin obj

clean:
	rm -r bin/ obj/
