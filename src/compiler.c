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

/**
   This is a very simple implementation of a bytecode compiler.
   Basically, all we do is take some instructions (for now, created in
   examples.h with a macro) and write them binary to a specified file.
 */
int main(int argc, char *argv[]) {
  if(argc > 1) {
    char* filename = argv[1];
    Instruction p[] = procedures();
    int length = sizeof(p) / sizeof(Instruction);
    FILE *file = fopen(filename, "w+b");
    fwrite(p, sizeof(Instruction), length, file);
    fclose(file);
    return 0;
  } else {
    fprintf(stderr, "Error: Please specify an output filename to save bytcode to.\n");
    return -1;
  }
}
