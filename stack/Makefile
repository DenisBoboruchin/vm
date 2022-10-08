INC_DIR = include

CC = clang++
CFLAGS = -c -Wall -Wextra -Werror -I$(INC_DIR)
TESTFLAGS = -fsanitize=address -g

all: test stack.gch main.o
	$(CC) main.o -o main


stack.gch: include/stack.hpp
	$(CC) $(CFLAGS) include/stack.hpp


main.o: stack.gch main.cpp
	$(CC) $(CFLAGS) main.cpp


test: stack.gch tests.o
	$(CC) tests.o -o test -lgtest

tests.o: tests/tests.cpp
	$(CC) $(CFLAGS) tests/tests.cpp


clean:
	rm *.o include/*.gch main test
	
