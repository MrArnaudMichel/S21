all: ls_ ls_a ls_l pwd_ find_ grep_

filesystem.o: filesystem.c filesystem.h
	gcc -c filesystem.c

ls_: ls_.c filesystem.o
	gcc -o ls_ ls_.c filesystem.o

ls_a: ls_a.c filesystem.o
	gcc -o ls_a ls_a.c filesystem.o

ls_l: ls_l.c filesystem.o
	gcc -o ls_l ls_l.c filesystem.o

pwd_: pwd.c filesystem.o
	gcc -o pwd_ pwd.c filesystem.o

find_: find.c filesystem.o
	gcc -o find_ find.c filesystem.o

grep_: grep.c filesystem.o
	gcc -o grep_ grep.c filesystem.o

clean:
	rm *.o
