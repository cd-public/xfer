CC=gcc
CFLAGS= -I.

test: test.o pmap_sloppy.o
	$(CC) -o tester test.o pmap_sloppy.o $(CFLAGS)

clean:
	rm -f *.o tester
