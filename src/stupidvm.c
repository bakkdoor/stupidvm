#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"
#include "stack.h"


/* register is 8 bit */
typedef unsigned char REGISTER; 

/* define 16 8-bit registers */
REGISTER regs[16] = {0,0,0,0,
                     0,0,0,0,
                     0,0,0,0,};

/* 8-bit programm counter */
REGISTER PC; 


COMMAND* create_programm(void)
{
  COMMAND* p = malloc(10 * sizeof(COMMAND));
  int i;
  
  for(i=0; i<10; i++) {
    p[i] = i;
  }

  return p;
}


void run(COMMAND* programm)
{
  COMMAND cmd;
  OPCODE opc;
  Stack* stack;
  init(stack);
  PC = 0;
    
  while(1) {
    cmd = programm[PC++];
    
    opc = opcode(cmd);
    
    if(opc == POP) {
      pop(stack);
    }
  }
}

int main(int argc, char *argv[])
{
  run(create_programm());
  return 0;
}
