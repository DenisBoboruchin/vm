INC_DIR = include

CC = clang++
CFLAGS = -c -g -Wall -Wextra -Werror -I$(INC_DIR)

all: main.o
	$(CC) main.o -o main

stack.o: src/stack.cpp
	$(CC) $(CFLAGS) src/stack.cpp
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

#clang-tidy: main.cpp include/stack.h
#	clang-tidy include/stack.h main.cpp


test: tests.o
	$(CC) tests.o -o test -lgtest

tests.o: tests/tests.cpp
	$(CC) $(CFLAGS) tests/tests.cpp


clean:
	rm *.o include/*.gch main test
	
