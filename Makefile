cc = gcc
cc_flags = -Wall -Wstrict-prototypes -pedantic

common_dir = src/common
vm_dir = src/vm
asm_dir = src/asm
common_files = $(common_dir)/stack.c $(common_dir)/utils.c $(common_dir)/opcodes.c
vm_files = $(vm_dir)/main.c $(vm_dir)/stupidvm.c
asm_files = $(asm_dir)/assembler.c $(asm_dir)/instructions.c

vm_out = svm
asm_out= sasm

all: sasm svm
svm: $(common_files) $(vm_files)
	$(cc) $(cc_flags) $(common_files) $(vm_files) -o $(vm_out)
sasm: $(common_files) $(asm_files)
	$(cc) $(cc_flags) $(common_files) $(asm_files) -o $(asm_out)
doc:
	doxygen
clean:
	rm -f $(vm_out) $(asm_out)
	rm -rf doc/