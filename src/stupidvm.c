#include "includes.h"

/* register is 8 bit */
typedef unsigned char Register; 

/* define 16 8-bit registers */
Register regs[16] = {0,0,0,0,
                     0,0,0,0,
                     0,0,0,0,};
/**
   status register.
   holds information about certain status flags.
   including:
   LSB: indicating if last boolean operation was true or false.
*/
Register status;

/* 32-bit programm counter */
int PC; 

void run(Command* programm)
{
  Command cmd;
  Operand opc, op1, op2;
  Stack stack;
  Register reg1, reg2;
  init(&stack);
  PC = 0;
  status = 0;
 
  while(1) { 
    cmd = programm[PC];
    opc = opcode(cmd);
    op1 = first(cmd);
    op2 = second(cmd);
    
    switch(opc) {
    case POP:
      regs[op1] = pop(&stack);
      break;
    case PUSH:
      push(&stack, regs[op1]);   /* push value into stack */
      break;
    case MUL:
      reg1 = regs[op1];
      reg2 = regs[op2];
      regs[op1] = reg1 * reg2;
      break;
    case SUB:
      reg1 = regs[op1];
      reg2 = regs[op2];
      regs[op1] = reg1 - reg2;
      break;
    case DIV:
      reg1 = regs[op1];
      reg2 = regs[op2];
      regs[op1] = reg1 / reg2;
      break;
    case ADDI:
      regs[op2] += op1;
      break;
    case MULI:
      regs[op2] *= op1;
      break;
    case SUBI:
      regs[op2] -= op1;
      break;
    case DIVI:
      regs[op2] /= op1;
      break;
    case LOAD:
      /* needs to be implemented */
      break;
    case LOADI:
      regs[op2] = op1;
      break;
    case MOV:
      regs[op2] = regs[op1];
      break;
    case JMP:
      PC = op1;
      break;
    case JMPZ:
      if(!status) {
        PC = op1;
      }
      break;
    case COM:
      regs[op1] = ~regs[op1];
      break;
    case NEG:
      regs[op1] = regs[op1] * -1;
      break;
    case CALL:
      /* needs to be implemented */
      break;
    case RET:
      /* needs to be implemented */
      break;
    case PRINT:
      printf("%d\n", regs[op1]);
      break;
    case EQ:
      status = regs[op1] == regs[op2] ? 1 : 0;
      break;
    case NEQ:
      status = regs[op1] != regs[op2] ? 1 : 0;
      break;
    case CLR:
      regs[op1] = 0;
      break;
    case HALT:
      printf("halting machine.\n");
      return;
    }
    PC++;
  }
}


/**
   Main function.
   Starts the vm execution process.
*/
int main(int argc, char *argv[])
{
  Command p[] = example1();
  run(p);
  return 0;
}
