dir = src
common_files = $(dir)/stack.c
vm_files = $(dir)/main.c $(dir)/stupidvm.c
compiler_files = $(dir)/compiler.c

all: vm compiler
vm: $(common_files) $(vm_files)
	gcc -Wall -Wstrict-prototypes -ansi $(common_files) $(vm_files) -o stupidvm
strict: $(common_files) $(vm_files)
	gcc -Wall -Wstrict-prototypes -ansi -pedantic $(common_files) $(vm_files) -o stupidvm
compiler: $(common_files) $(compiler_files)
	gcc -Wall -Wstrict-prototypes -ansi -pedantic $(common_files) $(compiler_files) -o compiler
clean:
	rm -f src/*.o
	rm -f stupidvm
	rm -f compiler
test: vm compiler
	./stupidvm