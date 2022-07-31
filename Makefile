CC=gcc
FLAGS=-O3 -Wall -Wextra -std=c89 -pedantic

main: main.c
	$(CC) $(FLAGS) main.c -o main
