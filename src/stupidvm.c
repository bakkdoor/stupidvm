#include "includes.h"

/* register is 8 bit */
typedef unsigned char Register; 

/* maximum value for registers (all bits = 1) */
#define MAX_REG_VAL 0xFF

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

/* size of vm memory */
#define MAX_VM_MEMORY 65536 /* for now, 2^16 = 64k bytes */
Register* memory;

void run(Command* programm)
{
  Command cmd;
  Operand opc, op1, op2;
  Stack stack;
  init(&stack);
  PC = 0;
  status = 0;

  memory = malloc(MAX_VM_MEMORY * sizeof(Register));

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
      push(&stack, regs[op1]);
      break;
    case ADD:
      regs[op1] += regs[op2];
      break;
    case MUL:
      regs[op1] *= regs[op2];
      break;
    case SUB:
      regs[op1] -= regs[op2];
      break;
    case DIV:
      regs[op1] /= regs[op2];
      break;
    case ADDI:
      regs[op1] += op2;
      break;
    case MULI:
      regs[op1] *= op2;
      break;
    case SUBI:
      regs[op1] -= op2;
      break;
    case DIVI:
      regs[op1] /= op2;
      break;
    case LOAD:
      /* needs to be implemented */
      break;
    case LOADI:
      regs[op1] = op2;
      break;
    case MOV:
      regs[op1] = regs[op2];
      break;
    case JMP:
      PC = PC + op1;
      break;
    case JMPC:
      if(status == 1) {
        PC = PC + op1;
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
    case SET:
      regs[op1] = MAX_REG_VAL;
      break;
    case ST:
      memory[regs[op1]] = regs[op2];
      break;
    case INC:
      regs[op1] = regs[op1] + 1;
      break;
    case DEC:
      regs[op1] = regs[op1] - 1;
      break;
    case JMPBC:
      if(status == 1) {
        PC = PC - op1;
      }
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
  Command p[] = fibonacci();
  run(p);
  
  puts("=====================");
  printf("dumping memory:\n");
  for(PC = 0; PC < 14; PC ++) {
    printf("memory[%d] is: %d\n", PC, memory[PC]);
  }

  return 0;
}
