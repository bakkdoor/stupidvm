all: vm test
vm: 
	gcc -Wall -Wstrict-prototypes -ansi src/*.c -o stupidvm
strict:
	gcc -Wall -Wstrict-prototypes -ansi -pedantic src/*.c -o stupidvm
clean:
	rm -f src/*.o
	rm -f stupidvm
test: vm
	./stupidvm