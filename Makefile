CC=C:\MinGW\bin\gcc
INCLUDE=-Iinclude
LIBS=-Llib
FLAGS=-O3 -m32 -Wall -Wextra

main: main.c
	$(CC) $(INCLUDE) $(LIBS) $(FLAGS) main.c -o main
