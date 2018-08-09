# compiler to be used
CC=g++

# flags to pass to compiler
CFLAGS=-g -Wall -std=c++11

# flags to pass to compiler
FILES=driver.cpp

all: bst

bst: $(FILES) bst.h driver.cpp
	$(CC) $(CFLAGS) $(FILES) -o $@

.PHONY: clean

clean:
	rm test