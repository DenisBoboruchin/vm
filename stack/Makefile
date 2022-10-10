INC_DIR = include

CC = clang++
CXXFLAGS = -c -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS = 

FLAGSSANITIZE = -fsanitize=address -fsanitize=undefined

LDFLAGS += $(FLAGSSANITIZE)
CXXFLAGS += $(FLAGSSANITIZE)



all: test stack.gch main.o
	$(CC) $(LDFLAGS) main.o -o main


stack.gch: include/stack.hpp
	$(CC) $(CXXFLAGS) include/stack.hpp


main.o: stack.gch main.cpp
	$(CC) $(CXXFLAGS) main.cpp
	

test: stack.gch tests.o
	$(CC) $(LDFLAGS) tests.o -o test -lgtest

tests.o: tests/tests.cpp
	$(CC) $(CXXFLAGS) tests/tests.cpp


clang-tidy: clang-tidy-main clang-tidy-tests

clang-tidy-main:
	clang-tidy main.cpp -- -I$(INC_DIR)

clang-tidy-tests:
	clang-tidy tests/tests.cpp -- -I$(INC_DIR)


clang-format: clang-format-main clang-format-stack.hpp clang-format-tests

clang-format-main:
	clang-format -i main.cpp

clang-format-stack.hpp:
	clang-format -i include/stack.hpp

clang-format-tests:
	clang-format -i tests/tests.cpp



clean:
	rm *.o include/*.gch main test
	
