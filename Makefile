CC=gcc
FLAGS=-O3 -Wall -Wextra -std=c89 -pedantic

all: main main_wc

main: main.c
	$(CC) $(FLAGS) main.c -o main

main_wc: main_wc.c
	$(CC) $(FLAGS) main_wc.c -o main_wc