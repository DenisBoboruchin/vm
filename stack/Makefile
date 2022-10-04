INC_DIR = include

CC = g++
CFLAGS = -c -g -Wall -Wextra -Werror -I$(INC_DIR)

all: main.o stack.o
	$(CC) main.o stack.o -o main -lgtest

stack.o: src/stack.cpp
	$(CC) $(CFLAGS) src/stack.cpp
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp


clean:
	rm *.o main
	
