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

/**
   @brief Starts the main evaluation process of the vm.
   
   Basically, we start an infinite loop and run until we hit the HALT
   instruction, which stops the virtual machine. This means, that the
   programm itself is responsible for telling the VM when to
   stop. This might change in the future though, as I'm still unsure,
   if this is a good idea...
   We then check the opcode of each instruction within the loop and
   execute the appropriate code for that opcode. Pretty simple &
   stupid if you ask me ;)
   
   @param programm An array of Instruction values representing the
   programm to be executed.
 */
void run(Instruction* programm)
{
  Instruction ins;
  Byte opc;
  Operand op1, op2;
  Stack *stack, *callstack;
  int i;

  stack = st_init();
  callstack = st_init();
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
      regs[op1] = st_pop(stack);
      break;
    case PUSH:
      st_push(stack, regs[op1]);
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
      PC = op1;
      continue;
      break;
    case JMPC:
      if(status == 1) {
        PC = op1;
        status = 0;
        continue;
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
        st_push(callstack, regs[i]);
      }
      st_push(callstack, status);
      st_push(callstack, PC);
      PC = op1;
      continue;
      break;
    case RET:
      /* return from procedure, restoring all old values in opposite
         order */
      PC = st_pop(callstack);
      status = st_pop(callstack);
      for(i=(NUM_REGS - 1); i > -1; i--) {
        regs[i] = st_pop(callstack);
      }
      break;
    case PRINT:
      printf("%d\n", regs[op1]);
      break;
    case READ:
      scanf("%d", &regs[op1]);
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
    case SIS:
      if(status == 1) {
        PC++;
      }
      break;
    case HALT:
      printf("halting machine.\n");
      return;
    case LD:
      regs[op1] = memory[regs[op2]];
      break;
    default:
      printf("ERROR: Unknown Opcode: %d\nAborting!\n", opc);
      return;

    }
    PC++;
  }
}

/**
   @brief Execute a programm from a given bytecode .svm file.
   
   Open the file, read it into memory and run it via run().
   That's basically it.
   
   @param filename Filename of the bytecode .svm file to be executed.
 */
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
  if(!buffer) {
    errormsg("Memory error!");
    fclose(file);
    return;
  }
  
  /* read file into buffer */
  fread(buffer, flength, (flength / sizeof(Instruction)), file);
  fclose(file);
  
  run(buffer);

  /* free memory when done */
  free(buffer);
}

/**
   @brief Prints out the first given amount of memory slots in the VM.

   @param amount The amount of memory slots to print out.
 */
void print_memory(int amount) {
  int i;
  puts("=====================");
  printf("dumping memory:\n");
  for(i = 0; i < amount; i ++) {
    printf("memory[%d] is: %d\n", i, memory[i]);
  }
}
