#include "includes.h"

/* register is 8 bit */
typedef unsigned char REGISTER; 

/* define 16 8-bit registers */
REGISTER regs[16] = {0,0,0,0,
                     0,0,0,0,
                     0,0,0,0,};
/**
   status register.
   holds information about certain status flags.
   including:
   LSB: indicating if last boolean operation was true or false.
*/
REGISTER status;

/* 8-bit programm counter */
int PC; 


COMMAND* example_programm(void)
{
  COMMAND* p = malloc(10 * sizeof(COMMAND));

  p[0] = build_cmd(LOADI, 10, 0);
  p[1] = build_cmd(LOADI, 5, 1);
  p[2] = build_cmd(MUL, 0, 1);
  p[3] = build_cmd(PUSH, 1, 0);
  p[4] = build_cmd(LOADI, 3, 1);
  p[5] = build_cmd(MUL, 0, 1);
  p[6] = build_cmd(POP, 1, 0);
  p[7] = build_cmd(PRINT, 0, 0);
  p[8] = build_cmd(PRINT, 1, 0);
  p[9] = build_cmd(HALT, 0, 0);

  return p;
}


void run(COMMAND* programm)
{
  COMMAND cmd;
  OPERAND opc, source, destination;
  Stack stack;
  REGISTER reg1, reg2;
  init(&stack);
  PC = 0;
  status = 0;
 
  while(1) { 
    cmd = programm[PC];
    opc = opcode(cmd);
    
    switch(opc) {
    case POP:
      regs[first_op(cmd)] = pop(&stack);
      break;
    case PUSH:
      source = first_op(cmd); /* register number */
      reg1 = regs[source]; /* value of register */
      push(&stack, reg1);  /* push value into stack */
      break;
    case MUL:
      destination = first_op(cmd);
      reg1 = regs[destination];
      reg2 = regs[second_op(cmd)];
      regs[destination] = reg1 * reg2;
      break;
    case SUB:
      destination = first_op(cmd);
      reg1 = regs[destination];
      reg2 = regs[second_op(cmd)];
      regs[destination] = reg1 - reg2;
      break;
    case DIV:
      destination = first_op(cmd);
      reg1 = regs[destination];
      reg2 = regs[second_op(cmd)];
      regs[destination] = reg1 / reg2;
      break;
    case ADDI:
      destination = second_op(cmd);
      regs[destination] += first_op(cmd);
      break;
    case MULI:
      destination = second_op(cmd);
      regs[destination] *= first_op(cmd);
      break;
    case SUBI:
      destination = second_op(cmd);
      regs[destination] -= first_op(cmd);
      break;
    case DIVI:
      destination = second_op(cmd);
      regs[destination] /= first_op(cmd);
      break;
    case LOAD:
      /* needs to be implemented */
      break;
    case LOADI:
      destination = second_op(cmd);
      regs[destination] = first_op(cmd);
      break;
    case MOV:
      regs[second_op(cmd)] = regs[first_op(cmd)];
      break;
    case JMP:
      PC = first_op(cmd);
      break;
    case JMPZ:
      if(!status) {
        PC = first_op(cmd);
      }
      break;
    case COM:
      destination = first_op(cmd);
      regs[destination] = ~regs[destination];
      break;
    case NEG:
      destination = first_op(cmd);
      regs[destination] = regs[destination] * -1;
      break;
    case CALL:
      /* needs to be implemented */
      break;
    case RET:
      /* needs to be implemented */
      break;
    case PRINT:
      printf("%d\n", regs[first_op(cmd)]);
      break;
    case HALT:
      printf("halting machine.\n");
      return;
    }
    PC++;
  }
}

int main(int argc, char *argv[])
{
  run(example_programm());
  return 0;
}
