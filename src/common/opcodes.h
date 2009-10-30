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

/* short-hand macro for creating instructions */
#define instruction(name,a,b) {name,a,b}

#define POP(reg) instruction(POP, reg, 0)
#define PUSH(reg) instruction(PUSH, reg, 0)
#define ADD(reg,reg2) instruction(ADD, reg, reg2)
#define SUB(reg,reg2) instruction(SUB, reg, reg2)
#define MUL(reg,reg2) instruction(MUL, reg, reg2)
#define DIV(reg,reg2) instruction(DIV, reg, reg2)
#define ADDI(reg,reg2) instruction(ADDI, reg, reg2)
#define SUBI(reg,reg2) instruction(SUBI, reg, reg2)
#define MULI(reg,reg2) instruction(MULI, reg, reg2)
#define DIVI(reg,reg2) instruction(DIVI, reg, reg2)
#define LOAD(reg,addr) instruction(LOAD, reg, addr)
#define LOADI(reg,val) instruction(LOADI, reg, val)
#define MOV(reg_dest,reg_src) instruction(MOV, reg_dest, reg_src)
#define JMP(addr) instruction(JMP, addr, 0)
#define JMPC(addr) instruction(JMPC, addr, 0)
#define COM(reg) instruction(COM, reg, 0)
#define NEG(reg) instruction(NEG, reg, 0)
#define CALL(func) instruction(CALL, func, 0)
#define RET() instruction(RET, 0, 0)
#define PRINT(reg) instruction(PRINT, reg, 0)
#define EQ(reg,reg2) instruction(EQ, reg, reg2)
#define NEQ(reg,reg2) instruction(NEQ, reg, reg2)
#define CLR(reg) instruction(CLR, reg, 0)
#define SET(reg) instruction(SET, reg, 0)
#define ST(reg_addr,reg) instruction(ST, reg_addr, reg)
#define INC(reg) instruction(INC, reg, 0)
#define DEC(reg) instruction(DEC, reg, 0)
#define SIS() instruction(SIS, 0, 0)
#define HALT() instruction(HALT, 0, 0)

/* function definitions */
Opcode opcode_from_string(char *string);

#endif
