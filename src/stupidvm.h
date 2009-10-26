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

/* register is 32 bit */
typedef int Register; 

/* maximum value for registers (all bits = 1) */
#define MAX_REG_VAL 0xFFFFFFFF

#define NUM_REGS 32

/* size of vm memory */
#define MAX_VM_MEMORY 65536 /* for now, 2^16 = 64k bytes */

/* function definitions */
void run(Instruction* programm);
void run_from_file(char* filename);
