#include "includes.h"

/* register is 32 bit */
typedef int Register; 

/* maximum value for registers (all bits = 1) */
#define MAX_REG_VAL 0xFFFFFFFF

#define NUM_REGS 32

/* define NUM_REGS 32-bit registers */
Register regs[NUM_REGS] = {0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0};
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

void run(Instruction* programm)
{
  Instruction ins;
  Byte opc;
  Operand op1, op2;
  Stack stack, callstack;
  init(&stack);
  init(&callstack);
  PC = 0;
  status = 0;
  int i;

  memory = malloc(MAX_VM_MEMORY * sizeof(Register));

  while(1) { 
    ins = programm[PC];
    opc = ins.opcode;
    op1 = ins.op1;
    op2 = ins.op2;

    printf("op1=%d - PC=%d\n", op1, PC);

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
      regs[op1] = memory[op2];
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
      /* save PC, status & registers */
      for(i=0; i<NUM_REGS; i++) {
        push(&callstack, regs[i]);
      }
      push(&callstack, status);
      push(&callstack, PC);
      PC = op1;
      continue;
      break;
    case RET:
      /* return from procedure, restoring all old values in opposite
         order */
      PC = pop(&callstack);
      status = pop(&callstack);
      for(i=14; i>= 0; i--) {
        regs[i] = pop(&callstack);
      }
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
        continue;
      }
      break;
    case SIS:
      if(status == 1) {
        PC++;
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
  int amount = 40;
  /* Instruction p[] = fibonacci(amount); */
  Instruction p[] = procedures();
  run(p);
  
  puts("=====================");
  printf("dumping memory:\n");
  for(PC = 0; PC < amount; PC ++) {
    printf("memory[%d] is: %d\n", PC, memory[PC]);
  }

  return 0;
}
