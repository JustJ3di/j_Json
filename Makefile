all:main

main:prove.o hjson.o
	gcc -o  prova prove.o hjson.o -Wall -Wextra

prove.o: prove.c
	gcc -c -o prove.o prove.c -Wall -Wextra

hjson.o: src/hjson.c
	gcc -c -o hjson.o src/hjson.c -Wall -Wextra

clean:
	rm -f *.o
	rm -f prova
