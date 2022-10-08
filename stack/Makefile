INC_DIR = include

CC = clang++
CFLAGS = -c -Wall -Wextra -Werror -I$(INC_DIR)
TESTFLAGS = -fsanitize=address -static-libasan -g


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


clang-tidy: clang-tidy-main clang-tidy-tests

clang-tidy-main:
	clang-tidy main.cpp -- -I$(INC_DIR)

clang-tidy-tests:
	clang-tidy tests/tests.cpp -- -I$(INC_DIR)


clang-format: clang-format-main clang-format-stack.hpp clang-format-tests

clang-format-main:
	clang-format main.cpp

clang-format-stack.hpp:
	clang-format include/stack.hpp

clang-format-tests:
	clang-format tests/tests.cpp



clean:
	rm *.o include/*.gch main test
	
