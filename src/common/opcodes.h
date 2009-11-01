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

#ifndef OPCODES_H
#define OPCODES_H

/***********************************
 opcode & operand macro declarations
************************************/

typedef enum {
  POP = 0,       /* pop value from stack to register */
  PUSH = 1,      /* push value from register to stack*/
  ADD = 2,       /* add two registers and store in first */
  MUL = 3,       /* multiply two registers and store in first */
  SUB = 4,       /* subtract two registers and store in first */
  DIV = 5,       /* divide two registers and store in first */
  ADDI = 6,      /* add immidiate with register and store in register */
  MULI = 7,      /* multiply immidiate with register and store in register */
  SUBI = 8,      /* subtract immidiate with register and store in register */
  DIVI = 9,      /* divide immidiate with register and store in register */
  LOAD = 10,     /* load value into register from adress (memory) */
  LOADI = 11,    /* load immidiate (literal) into register (first arg) */
  MOV = 12,      /* move (copy) value from second to first register */
  JMP = 13,      /* jump (branch) to adress (unconditional branch) */
  JMPC = 14,     /* jump (branch) to adress conditionally (if status = 1) */
  COM = 15,      /* (binary) complement value in register */
  NEG = 16,      /* negate value in register */
  CALL = 17,     /* call a function */
  RET = 18,      /* return from function */
  PRINT = 19,    /* print content of register to stdout */
  READ = 20,     /* read number into register */
  EQ = 21,       /* set status = 1 if contents of registers equal */
  NEQ = 22,      /* opposite of EQ */
  CLR = 23,      /* clear register (set to zero) */
  SET = 24,      /* set register to max_val (all bits = 1) */
  ST = 25,       /* store indirect value to memory address in first
                    register from second register */
  LD = 26,       /* load indirect value into register from memory address */
  INC = 27,      /* increment (+1) register */
  DEC = 28,      /* decrement (-1) register */
  SIS = 29,      /* skip next instruction, if status = 1 */
  HALT = 30      /* halt/stop the machine */
} Opcode;

typedef unsigned char Byte;

/* operand is 32 bit */
typedef int Operand;  

/* Instructions consist of the opcode and up to two operands */
typedef struct {
  Byte opcode;
  Operand op1;
  Operand op2;
} Instruction;

/* function definitions */

/* maximum length of characters for an opcode instruction name */
#define MAX_OPCODE_LENGTH 5

/**
   @brief Returns an Opcode based on a string representing that opcode
   (usually coming from a parsed .sasm file).
   
   @param string The string representing the opcode.
   @return The opcode represented by the given string.
 */
Opcode opcode_from_string(char *string);

#endif
