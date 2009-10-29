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
   Main function.
   Starts the vm execution process.
*/
int main(int argc, char *argv[])
{
  if(argc > 1) {
    run_from_file(argv[1]);
  } else {
    fprintf(stderr, "Error: Please specify a .svm compiled bytecode file.\n");
    return -1;
  }
  
  /* for debugging purposes */
  /* print_memory(30); */
  
  return 0;
}
