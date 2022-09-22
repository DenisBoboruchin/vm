CC 		= g++
CFLAGS 	= -c -Wall -Wextra

all: main.o complex_num.o
	$(CC) main.cpp src/complex_num.cpp -o main -lgtest -pthread

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

complex_num.o: src/complex_num.cpp
	$(CC) $(CFLAGS) src/complex_num.cpp

clean:
	rm *.o main

