CC ?= gcc
CFLAGS ?= -Wall -Wextra

TEST_BINS = test/test1 test/test2 test/test3

all:main

main:prove.o hjson.o
	gcc -o  prova prove.o hjson.o -Wall -Wextra

prove.o: prove.c
	gcc -c -o prove.o prove.c -Wall -Wextra

hjson.o: src/hjson.c
	gcc -c -o hjson.o src/hjson.c -Wall -Wextra

test: $(TEST_BINS)
	./test/test1
	./test/test2
	./test/test3

test/%: test/%.c src/hjson.c src/hjson.h
	$(CC) $(CFLAGS) -o $@ $< src/hjson.c

clean:
	rm -f *.o
	rm -f prova
	rm -f $(TEST_BINS)

.PHONY: all clean test
