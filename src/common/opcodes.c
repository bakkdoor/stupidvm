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

Opcode opcode_from_string(char *string) {
  int i;
  int length;
  char opcodes[][MAX_OPCODE_LENGTH] = {
    "POP", "PUSH", "ADD", "MUL", "SUB",
    "DIV", "ADDI", "MULI", "SUBI", "DIVI",
    "LOAD", "LOADI", "MOV", "JMP", "JMPC",
    "COM", "NEG", "CALL", "RET", "PRINT", 
    "READ", "EQ", "NEQ", "CLR", "SET",
    "ST", "LD", "INC", "DEC", "SIS", 
    "HALT"
  };

  length = sizeof(opcodes) / MAX_OPCODE_LENGTH;

  for(i = 0; i < length; i++) {
    /* 
       ignore the case, so we allow instrunctions written in lower
       case as well 
    */
    if(strncasecmp(opcodes[i], string, strlen(string)) == 0) {
      return (Opcode)i;
    }
  }
  
  /* no correct opcode found -> error */
  fprintf(stderr, "ERROR: Illegal instruction name: %s\n", string);
  abort();
}
