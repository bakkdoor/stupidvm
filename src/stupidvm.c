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

#include "includes.h"

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
Register* memory;

void run(Instruction* programm)
{
  Instruction ins;
  Byte opc;
  Operand op1, op2;
  Stack stack, callstack;
  int i;

  init(&stack);
  init(&callstack);
  PC = 0;
  status = 0;

  memory = malloc(MAX_VM_MEMORY * sizeof(Register));

  while(1) { 
    ins = programm[PC];
    opc = ins.opcode;
    op1 = ins.op1;
    op2 = ins.op2;

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
      for(i=(NUM_REGS - 1); i > -1; i--) {
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


void run_from_file(char* filename) {
  Instruction* buffer;
  FILE *file;
  unsigned long flength;
  
  file = fopen(filename, "rb");
  if (!file) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return;
  }
  
  /* get file length */
  flength = file_length(file);
  
  /* alloc instruction buffer memory */
  buffer = (Instruction*) malloc(flength+1);
  if (!buffer) {
    errormsg("Memory error!");
    fclose(file);
    return;
  }
  
  /* read file into buffer */
  fread(buffer, flength, 1, file);
  fclose(file);
  
  run(buffer);

  /* free memory when done */
  free(buffer);
}
