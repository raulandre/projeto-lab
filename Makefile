CC = clang
FLAGS = -Werror -Wall -O2 -I./include

all: bin main.o client.o list.o queue.o mainmenu.o serial.o
	$(CC) $(FLAGS) obj/main.o obj/client.o obj/list.o obj/queue.o obj/mainmenu.o obj/serial.o -lncurses -o bin/a.out 

main.o: src/main.c
	$(CC) $(FLAGS) -c src/main.c -o obj/main.o

client.o: src/client.c include/client.h
	$(CC) $(FLAGS) -c src/client.c -o obj/client.o

list.o: src/list.c include/list.h
	$(CC) $(FLAGS) -c src/list.c -o obj/list.o

queue.o: src/queue.c include/queue.h
	$(CC) $(FLAGS) -c src/queue.c -o obj/queue.o

mainmenu.o: src/mainmenu.c include/mainmenu.h
	$(CC) $(FLAGS) -c src/mainmenu.c -o obj/mainmenu.o

serial.o: src/serial.c include/serial.h
	$(CC) $(FLAGS) -c src/serial.c -o obj/serial.o

bin:
	mkdir bin obj

clean:
	@echo "Limpando projeto ..."
	@rm -rf bin obj
	@find . -name "*.dat" -exec rm -f {} \;
