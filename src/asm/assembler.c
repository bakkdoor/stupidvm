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

/**
   Print out usage help.
 */
void usage(void) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "./compiler source_file.sasm output_file.svm\n");
}

/**
   Runs the c preprocessor (cpp) on a given file via popen() and
   returns a FILE handle created by that.
   
   @param source_filename The name of the source file.
   @return FILE handle to the cpp-processed source file.
 */
FILE* exec_cpp(char *source_filename) {
  char command[500] = {"cpp "};
  strcat(command, source_filename);
  return popen(command, "r");
}

/**
   Bytecode assembler main entry point. Starts the compilation process
   to binary bytecode.
 */
int main(int argc, char *argv[]) {
  if(argc == 3) {
    char *source_filename = argv[1];
    char *dest_filename = argv[2];
    FILE *source, *destination;
    /* pointer to first element in list */
    InstructionWords *words;
    
    source = exec_cpp(source_filename);
    destination = fopen(dest_filename, "w+b");

    /* check, if opening worked */
    if(!source) {
      fprintf(stderr, "ERROR with opening file: %s", source_filename);
    }
    if(!destination) {
      fprintf(stderr, "ERROR with opening file: %s", dest_filename);
    }
      
    /* build up InstructionWords list */
    words = build_instruction_words(source);

    /* and now compile them to the destination binary bytecode file */
    printf("compiling to %s: ", dest_filename);
    compile_instruction_words(words, destination);
    printf("\n");

    /* free all InstructionWords elements */
    free_list(words);

    fclose(source);
    fclose(destination);
    
    return 0;
  } else {
    fprintf(stderr, "Error: Please specify an output filename to save bytecode to.\n");
    usage();
    return -1;
  }
}
