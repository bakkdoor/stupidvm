#ifndef OPCODES_H
#define OPCODES_H

#define OPC_SIZE 6          /* number of bits for OPCODES */
#define COMMAND_SIZE 16     /* number of bits for COMMANDS */
#define OP_SIZE 5           /* number of bits for OPERANDS */

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
  LOAD = 0x0A,     /* load from adress (memory) into register */
  LOADI = 0x0B,    /* load immidiate (literal) into register */
  MOV = 0x0C,      /* move (copy) value from first to second register */
  JMP = 0x0D,      /* jump (branch) to adress (unconditional branch) */
  JMPZ = 0x0E,     /* jump (branch) to adress if last operation was zero (conditional branch) */
  COM = 0x0F,      /* (binary) complement value in register */
  NEG = 0x10,      /* negate value in register */
  CALL = 0x11,     /* call a function */
  RET = 0x12,      /* return from function */
  PRINT = 0x13,    /* print content of register to stdout */
  HALT = 0x14      /* halt/stop the machine */
} OPCODE;

/*
  command is 32 bit:  
  6 bits for opcode (0x00 - 0xFF + 1 extra bit (not used yet)) (possibly up to 255 built-in operations)
  5 bits for each operand (either adress of register or literal value)
 */
typedef unsigned short COMMAND; 

/* operand is 5 bit (first 3 bits are ignored) */
typedef unsigned char OPERAND;  


/************************
   function declarations
*************************/

OPERAND first_op(COMMAND c);
OPERAND second_op(COMMAND c);
OPCODE  opcode(COMMAND c);

COMMAND build_cmd(OPCODE opcode, OPERAND op1, OPCODE op2);

#endif
