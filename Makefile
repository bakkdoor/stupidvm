common_dir = src/common
vm_dir = src/vm
asm_dir = src/asm
common_files = $(common_dir)/stack.c $(common_dir)/utils.c $(common_dir)/opcodes.c
vm_files = $(vm_dir)/main.c $(vm_dir)/stupidvm.c
asm_files = $(asm_dir)/assembler.c $(asm_dir)/instructions.c

all: sasm svm
svm: $(common_files) $(vm_files)
	gcc -Wall -Wstrict-prototypes -ansi -pedantic $(common_files) $(vm_files) -o svm
sasm: $(common_files) $(asm_files)
	gcc -Wall -Wstrict-prototypes -pedantic $(common_files) $(asm_files) -o sasm
clean:
	rm -f src/*.o
	rm -f svm
	rm -f sasm