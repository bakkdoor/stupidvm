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
  POP = 0x00,      /* pop value from stack to register */
  PUSH = 0x01,     /* push value from register to stack*/
  ADD = 0x02,      /* add two registers and store in first */
  MUL = 0x03,      /* multiply two registers and store in first */
  SUB = 0x04,      /* subtract two registers and store in first */
  DIV = 0x05,      /* divide two registers and store in first */
  ADDI = 0x06,     /* add immidiate with register and store in register */
  MULI = 0x07,     /* multiply immidiate with register and store in register */
  SUBI = 0x08,     /* subtract immidiate with register and store in register */
  DIVI = 0x09,     /* divide immidiate with register and store in register */
  LOAD = 0x0A,     /* load value into register from adress (memory) */
  LOADI = 0x0B,    /* load immidiate (literal) into register (first arg) */
  MOV = 0x0C,      /* move (copy) value from second to first register */
  JMP = 0x0D,      /* jump (branch) to adress (unconditional branch) */
  JMPC = 0x0E,     /* jump (branch) to adress conditionally (if status = 1) */
  COM = 0x0F,      /* (binary) complement value in register */
  NEG = 0x10,      /* negate value in register */
  CALL = 0x11,     /* call a function */
  RET = 0x12,      /* return from function */
  PRINT = 0x13,    /* print content of register to stdout */
  EQ = 0x14,       /* set status = 1 if contents of registers equal */
  NEQ = 0x15,      /* opposite of EQ */
  CLR = 0x16,      /* clear register (set to zero) */
  SET = 0x17,      /* set register to max_val (all bits = 1) */
  ST = 0x18,       /* store indirect value to memory address in first
                      register from second register */
  INC = 0x19,      /* increment (+1) register */
  DEC = 0x1A,      /* decrement (-1) register */
  SIS = 0x1B,     /* skip next instruction, if status = 1 */
  HALT = 0x1C      /* halt/stop the machine */
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
