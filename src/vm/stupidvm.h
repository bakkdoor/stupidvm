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

/* register is 32 bit */
typedef int Register; 

/* maximum value for registers (all bits = 1) */
#define MAX_REG_VAL 0xFFFFFFFF

#define NUM_REGS 32

/* size of vm memory */
#define MAX_VM_MEMORY 65536 /* for now, 2^16 = 64k bytes */


/* function definitions */

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
   @param n_instructions Amount of instrunctions to be processed
   (usually the amount of instrunctions in programm)
 */
void run(Instruction* programm, unsigned long n_instructions);

/**
   @brief Execute a programm from a given bytecode .svm file.
   
   Open the file, read it into memory and run it via run().
   That's basically it.
   
   @param filename Filename of the bytecode .svm file to be executed.
 */
void run_from_file(char* filename);

/**
   @brief Prints out the first given amount of memory slots in the VM.

   @param amount The amount of memory slots to print out.
 */
void print_memory(int amount);
