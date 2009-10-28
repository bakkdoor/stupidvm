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


void build_instruction_words(InstructionWords *first, FILE *source) {
  char *line;
  char **read_words;
  InstructionWords *current = first;

  while( (line = read_line(source)) ) {
    /* 
       only write lines without a '#' in it (these lines are added
       by cpp and are ignored), also ignore lines with ';' (comments)  
    */
    if(!strchr(line, '#') && !strchr(line, ';') && !empty_string(line)) {
      printf("."); /* some output for the user to see */
      /* inst = instruction_from_line(line); */
      /* fwrite(&inst, sizeof(Instruction), 1, destination); */
      
      read_words = instruction_words(line);
      current->opcode = read_words[0];
      current->op1 = read_words[1];
      current->op2 = read_words[2];
      current->next = malloc(sizeof(InstructionWords));
      current->next->next = NULL;
      /* move pointer forward in list for next loop */
      current = current->next;
      
      free(read_words);
    }
    free(line);
  }
}

void compile_instruction_words(InstructionWords *first, FILE *destination) {
  InstructionWords *current = first;
}



void free_list(InstructionWords *first) {
  InstructionWords *last = first;
  InstructionWords *current = first;
  while(current->next) {
    last = current;
    current = current->next;
    free(last);
  }
  free(current);
}

