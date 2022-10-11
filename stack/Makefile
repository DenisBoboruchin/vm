INC_DIR= include

CC= clang++
CXXFLAGS= -c -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS= 

FLAGSSANITIZE= -fsanitize=address -fsanitize=undefined

LDFLAGS += $(FLAGSSANITIZE)
CXXFLAGS += $(FLAGSSANITIZE)


all: test stack.gch 

stack.gch: include/stack.hpp
	$(CC) $(CXXFLAGS) include/stack.hpp


stack_bool.o: stack.gch src/stack_bool.cpp
	$(CC) $(CXXFLAGS) src/stack_bool.cpp
	

test: stack.gch tests.o
	$(CC) $(LDFLAGS) tests.o -o test -lgtest

tests.o: tests/tests.cpp
	$(CC) $(CXXFLAGS) tests/tests.cpp


clang-tidy: clang-tidy-stack.cpp clang-tidy-tests

clang-tidy-stack.cpp:
	clang-tidy src/stack_bool.cpp -- -I$(INC_DIR)

clang-tidy-tests:
	clang-tidy tests/tests.cpp -- -I$(INC_DIR)


clang-format: clang-format-stack.cpp clang-format-stack.hpp clang-format-tests

clang-format-stack.cpp:
	clang-format -i src/stack_bool.cpp

clang-format-stack.hpp:
	clang-format -i include/stack.hpp

clang-format-tests:
	clang-format -i tests/tests.cpp



clean:
	rm *.o include/*.gch main test
	
