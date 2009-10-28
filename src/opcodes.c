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

/* maximum length of characters for an opcode instruction name */
#define MAX_OPCODE_LENGTH 5

Opcode opcode_from_string(char *string) {
  int i;
  int length;
  char opcodes[][MAX_OPCODE_LENGTH] = {
    "POP", "PUSH", "ADD", "MUL", "SUB",
    "DIV", "ADDI", "MULI", "SUBI", "DIVI",
    "LOAD", "LOADI", "MOV", "JMP", "JMPC",
    "COM", "NEG", "CALL", "RET", "PRINT", 
    "EQ", "NEQ", "CLR", "SET", "ST",
    "INC", "DEC", "JMPBC", "SIS", "HALT"
  };

  length = sizeof(opcodes) / MAX_OPCODE_LENGTH;

  for(i = 0; i < length; i++) {
    if(strncmp(opcodes[i], string, strlen(string)) == 0) {
      printf("opcode found is: %d\n", i);
      return (Opcode)i;
    }
  }
  
  /* no correct opcode found -> error */
  fprintf(stderr, "ERROR: Illegal instruction name: %s\n", string);
  abort();
}
