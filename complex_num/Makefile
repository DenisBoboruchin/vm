INC_DIR = include

CC 		= g++
CFLAGS 	= -c -Wall -Wextra -I$(INC_DIR)

all: main.o complex_num.o
	$(CC) main.o complex_num.o -o main -lgtest

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

complex_num.o: src/complex_num.cpp
	$(CC) $(CFLAGS) src/complex_num.cpp

clean:
	rm *.o main

