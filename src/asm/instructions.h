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

/*
   List type for instruction words read in from .sasm file
   Each list element points to a next element (or NULL).

   If element A.next points to element B, then element A was read in
   first and B will be compiled after A (and also run in this order,
   when executed by the vm).
*/
typedef struct instruction_words{
  char *opcode;
  char *op1;
  char *op2;
  struct instruction_words *next;
} InstructionWords;


char** instruction_words(char *line);
Instruction instruction_from_line(char *line);
void build_instruction_words(InstructionWords *first, FILE *source);
void compile_instruction_words(InstructionWords *first, FILE *destination);

/* list operations on InstructionWords */
void free_list(InstructionWords *first);