dir = src
common_files = $(dir)/stack.c $(dir)/utils.c $(dir)/opcodes.c
vm_files = $(dir)/main.c $(dir)/stupidvm.c
compiler_files = $(dir)/compiler.c

all: svm compiler
svm: $(common_files) $(vm_files)
	gcc -Wall -Wstrict-prototypes -ansi -pedantic $(common_files) $(vm_files) -o svm
compiler: $(common_files) $(compiler_files)
	gcc -Wall -Wstrict-prototypes -pedantic $(common_files) $(compiler_files) -o svmc
clean:
	rm -f src/*.o
	rm -f svm
	rm -f svmc
test: vm compiler
	./stupidvm