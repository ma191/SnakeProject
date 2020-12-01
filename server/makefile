
file=$(wildcard *.c)

SNAKE:$(file)
	gcc $(file) -I ../include/ -lcurses -lpthread -o SNAKE

DEBUG:
	gcc $(file) -I ../include -pthread -lcurses -o DEBUG -D _D
