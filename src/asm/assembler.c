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

#include "../includes.h"

void usage(void) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "./compiler source_file.sasm output_file.stupid\n");
}

/**
   returns 3-element array of string containing the values of:
   - opcode (instruction command name)
   - operand 1 (or 0, if not given)
   - operand 2 (or 0, if not given)
*/
char** instruction_words(char *line) {
  char **words;
  char *pch;
  int i = 0;
  
  words = malloc(sizeof(char*) * 3);

  pch = strtok(line, " ");
  while(pch != NULL) {
    words[i] = pch;
    pch = strtok(NULL, ", ");
    i++;
  }
  
  /* fill up any missing operands with 0 */
  for(; i < 3; i++) {
    words[i] = (char)0;
  }

  return words;
}

Instruction instruction_from_line(char *line) {
  Instruction ins;
  char **words = instruction_words(line);  

  ins.opcode = opcode_from_string(words[0]);
  ins.op1 = words[1] ? (Operand)atoi(words[1]) : (Operand)0;
  ins.op2 = words[2] ? (Operand)atoi(words[2]) : (Operand)0;

  return ins;
}

FILE* exec_cpp(char *source_filename) {
  char command[500] = {"cpp "};
  strcat(command, source_filename);
  return popen(command, "r");
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
    FILE *source, *destination;

    source = exec_cpp(source_file);
    destination = fopen(dest_file, "w+b");

    /* check, if opening worked */
    if(!source) {
      fprintf(stderr, "ERROR with opening file: %s", source_file);
    }
    if(!destination) {
      fprintf(stderr, "ERROR with opening file: %s", dest_file);
    }
    
    printf("compiling to %s: ", dest_file);
    /* compile line & write to destination file */
    while( (line = read_line(source)) ) {
      /* 
         only write lines without a '#' in it (these lines are added
         by cpp and are ignored), also ignore lines with ';' (comments)  
      */
      if(!strchr(line, '#') && !strchr(line, ';') && !empty_string(line)) {
        printf("."); /* some output for the user to see */
        inst = instruction_from_line(line);
        fwrite(&inst, sizeof(Instruction), 1, destination);
      }
      free(line);
    }

    printf("\n");

    fclose(source);
    fclose(destination);

    return 0;
  } else {
    fprintf(stderr, "Error: Please specify an output filename to save bytcode to.\n");
    usage();
    return -1;
  }
}
