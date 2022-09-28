INC_DIR = include

CC = g++
CFLAGS = -c -Wall -Wextra -Werror -I$(INC_DIR)

all: main.o stack.o
	$(CC) main.o stack.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

stack.o: src/stack.cpp
	$(CC) $(CFLAGS) src/stack.cpp
	
clean:
	rm *.o main
	
