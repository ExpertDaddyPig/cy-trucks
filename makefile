all: exec

functions: functions.c
	gcc -c functions.c -o functions.o

tri: tri.c
	gcc -c tri.c -o tri.o

exec: tri functions
	gcc tri.o functions.o -o tri

execbeep: tri functions beep
	gcc beep.o tri.o functions.o -o tri

clean: 
	rm -f tri *.o
