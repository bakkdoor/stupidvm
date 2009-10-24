#ifndef OPCODES_H
#define OPCODES_H

#define OPC_SIZE 6          /* number of bits for OPCODES */
#define COMMAND_SIZE 16     /* number of bits for COMMANDS */
#define OP_SIZE 5           /* number of bits for OPERANDS */

/* 1st operand matches bit mask: 000000 11111 00000 (= 0x3E0) */
#define FIRST_MSK 0x3E0

/* 2nd operand matches bit mask: 000000 00000 11111 (= 0x1F) */
#define SECOND_MSK 0x1F


/************************
   opcode & operand macro declarations
*************************/

#define first(c) ((c & FIRST_MSK) >> OP_SIZE)
#define second(c) (c & SECOND_MSK)
#define opcode(c) (c >> (COMMAND_SIZE - OPC_SIZE))


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
  JMPBC = 0x1B,
  HALT = 0x30      /* halt/stop the machine */
} Opcode;


#define POP(reg) command(POP, (reg), 0)
#define PUSH(reg) command(PUSH, (reg), 0)
#define ADD(reg,reg2) command(ADD, (reg), (reg2))
#define SUB(reg,reg2) command(SUB, (reg), (reg2))
#define MUL(reg,reg2) command(MUL, (reg), (reg2))
#define DIV(reg,reg2) command(DIV, (reg), (reg2))
#define ADDI(reg,reg2) command(ADDI, (reg), (reg2))
#define SUBI(reg,reg2) command(SUBI, (reg), (reg2))
#define MULI(reg,reg2) command(MULI, (reg), (reg2))
#define DIVI(reg,reg2) command(DIVI, (reg), (reg2))
#define LOAD(reg,addr) command(LOAD, (reg), (addr))
#define LOADI(reg,val) command(LOADI, (reg), (val))
#define MOV(reg_dest,reg_src) command(MOV, (reg_dest), (reg_src))
#define JMP(addr) command(JMP, (addr), 0)
#define JMPC(addr) command(JMPC, (addr), 0)
#define COM(reg) command(COM, (reg), 0)
#define NEG(reg) command(NEG, (reg), 0)
#define CALL(func) command(CALL, (func), 0)
#define RET() command(RET, 0, 0))
#define PRINT(reg) command(PRINT, (reg), 0)
#define EQ(reg,reg2) command(EQ, (reg), (reg2))
#define NEQ(reg,reg2) command(NEQ, (reg), (reg2))
#define CLR(reg) command(CLR, (reg), 0)
#define SET(reg) command(SET, (reg), 0)
#define ST(reg_addr,reg) command(ST, (reg_addr), (reg))
#define INC(reg) command(INC, (reg), 0)
#define DEC(reg) command(DEC, (reg), 0)
#define JMPBC(reg) command(JMPBC, (reg), 0)
#define HALT() command(HALT, 0, 0)


/*
  command is 16 bit:
  6 bits for opcode (0x00 - 0xFF + 1 extra bit (not used yet)) (possibly up to 255 built-in operations)
  5 bits for each operand (either adress of register or literal value)
 */
typedef unsigned short Command; 

/* operand is 5 bit (first 3 bits are ignored) */
typedef unsigned char Operand;  


/************************
   function declarations
*************************/

Command command(Opcode opcode, Operand op1, Operand op2);

#endif
