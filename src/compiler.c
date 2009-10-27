/*
    This file is part of stupidvm.

    stupidvm is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    stupidvm is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with stupidvm.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "includes.h"

void usage(void) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "./compiler source_file.sasm output_file.stupid\n");
}


Instruction instruction_from_line(char *line) {
  Instruction i;
  return i;
}

/**
   This is a very simple implementation of a bytecode compiler.
   Basically, all we do is take some instructions (for now, created in
   examples.h with a macro) and write them binary to a specified file.
 */
int main(int argc, char *argv[]) {
  if(argc == 3) {
    char *source_file = argv[1];
    char *dest_file = argv[2];
    char *line;
    Instruction inst;

    FILE *source = fopen(source_file, "r");
    FILE *destination = fopen(dest_file, "w+b");

    /* check, if opening worked */
    if(!source) {
      fprintf(stderr, "ERROR with opening file: %s", source_file);
    }
    if(!destination) {
      fprintf(stderr, "ERROR with opening file: %s", dest_file);
    }

    /* compile line & write to destination file */
    while( (line = read_line(source)) ) {
      inst = instruction_from_line(line);
      printf("writing instruction. opc: %d, op1: %d, op2: %d\n", inst.opcode, inst.op1, inst.op2);
      fwrite(&inst, sizeof(Instruction), sizeof(Instruction), destination);
      free(line);
    }

    fclose(source);
    fclose(destination);

    return 0;
  } else {
    fprintf(stderr, "Error: Please specify an output filename to save bytcode to.\n");
    usage();
    return -1;
  }
}
