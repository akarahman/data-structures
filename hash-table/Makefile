# compiler to be used
CC=g++

# flags to pass to compiler
CFLAGS=-g -Wall -std=c++11

# flags to pass to compiler
FILES=

all: test

test: $(FILES) test.cpp
	$(CC) $(CFLAGS) $(FILES) test.cpp -o $@

.PHONY: clean

clean:
	rm test