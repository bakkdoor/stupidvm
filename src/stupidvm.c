#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opcodes.h"
#include "stack.h"


/* register is 8 bit */
typedef unsigned char REGISTER; 

/* define 16 8-bit registers */
REGISTER regs[16] = {0,0,0,0,
                     0,0,0,0,
                     0,0,0,0,};

/* 8-bit programm counter */
int PC; 


COMMAND* create_programm(void)
{
  COMMAND* p = malloc(1 * sizeof(COMMAND));
  /* int i; */
  /* for(i=0; i<9; i++) { */
  /*   p[i] = build_cmd(HALT, 1, 2); */
  /* } */
  p[0] = build_cmd(HALT, 2, 3);
  return p;
}

void command_to_bin(COMMAND dez,char a[])
{
   char zw[33]; long r;

   a[0]='\0';
   while(dez>0)
   {
      r=dez%2;
      if(r==1) strcpy(zw,"1");
      else strcpy(zw,"0");
      strcat(zw,a);
      strcpy(a,zw);
      dez/=2;
   }
} 


void run(COMMAND* programm)
{
  COMMAND cmd;
  OPERAND opc;
  Stack stack;
  init(&stack);
  PC = 0;
  char str[16];
  command_to_bin(programm[PC], &str);

  printf("command is: %s\n", str);
  
  /*  while(1) { */
    cmd = programm[PC];
    opc = opcode(cmd);
    command_to_bin(opc, &str);
    printf("opcode is: %s\n", str);

    switch(opc) {
    case POP:
      pop(&stack);
      break;
    case 19:
      printf("halting machine\n");
      return;
    }
  /* } */
}

int main(int argc, char *argv[])
{
  run(create_programm());
  return 0;
}
