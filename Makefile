CC=gcc
FLAGS=-O3 -Wall -Wextra

main: main.c
	$(CC) $(INCLUDE) $(LIBS) $(FLAGS) main.c -o main
