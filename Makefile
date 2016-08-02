CFLAG=-std=c99
main: main.o list.o stack.o queue.o tree.o
	gcc main.o list.o stack.o queue.o tree.o -o main

main.o: main.c tree.h list.h stack.h queue.h
	gcc ${CFLAG} -c main.c

list.o: list.c list.h
	gcc ${CFLAG} -c list.c

queue.o: queue.c queue.h
	gcc ${CFLAG} -c queue.c

stack.o: stack.c stack.h
	gcc ${CFLAG} -c stack.c

tree.o: tree.c comparable_object.h tree.h
	gcc ${CFLAG} -c tree.c

clean:
	rm -rf *.o

