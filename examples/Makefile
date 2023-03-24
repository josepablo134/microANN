EXECUTABLE=example.exec
CFLAGS=-Wall -Werror -lm -I../include -I../cfg

.PHONY: all
all: uANN.o uHeap.o example.o uANN_extern.o
	gcc -o $(EXECUTABLE) $^ $(CFLAGS)

uANN.o: ../source/uANN.c
	gcc -c -o $@ $(CFLAGS) $^

uHeap.o: uHeap.c
	gcc -c -o $@ $(CFLAGS) $^

example.o: example.c
	gcc -c -o $@ $(CFLAGS) $^

uANN_extern.o: uANN_extern.c
	gcc -c -o $@ $(CFLAGS) $^

.PHONY: clean
clean:
	rm *.o *.exec
