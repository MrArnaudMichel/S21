all: tree_ head_ tail_

filesystem.o: filesystem.c filesystem.h
	gcc -c filesystem.c

tree_: tree_.c filesystem.o
	gcc -o tree_ tree_.c filesystem.o

head_: head_.c filesystem.o
	gcc -o head_ head_.c filesystem.o

tail_: tail_.c filesystem.o
	gcc -o tail_ tail_.c filesystem.o