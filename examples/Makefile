EXECUTABLE=example.exec
INCLUDE_DIR=../include
CFLAGS=-Wall -Werror -lm

.PHONY: all
all: uANN.o uHeap.o example.o
	gcc -o $(EXECUTABLE) $^ $(CFLAGS)

uANN.o: ../source/uANN.c
	gcc -c -o $@ $(CFLAGS) $^ -I$(INCLUDE_DIR)

uHeap.o: ../source/uHeap.c
	gcc -c -o $@ $(CFLAGS) $^ -I$(INCLUDE_DIR)

example.o: example.c
	gcc -c -o $@ $(CFLAGS) $^ -I$(INCLUDE_DIR)

.PHONY: clean
clean:
	rm *.o *.exec
