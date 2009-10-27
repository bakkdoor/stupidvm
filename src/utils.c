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

unsigned long file_length(FILE *file) {  
  unsigned long fl;

  fseek(file, 0, SEEK_END);
  fl = ftell(file);
  fseek(file, 0, SEEK_SET);

  return fl;
}

void errormsg(char *message) {
  fprintf(stderr, "ERROR: %s\n", message);
}
