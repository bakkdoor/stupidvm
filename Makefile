all: vm
vm: 
	gcc -Wall -Wstrict-prototypes -ansi -pedantic src/*.c -o stupidvm
clean:
	rm -f src/*.o
	rm -f stupidvm