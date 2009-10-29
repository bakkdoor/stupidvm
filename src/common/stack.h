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

#ifndef STACK_H
#define STACK_H

#define STACK_DEFAULT_SIZE 512

typedef struct
{
  Operand *values;
  int top;
  int size;
} Stack;

void st_push(Stack *S, Operand val);
Operand st_pop(Stack *S);
Stack* st_init(void);
Stack* st_init_size(int size);
Bool st_full(Stack *S);
Bool st_empty(Stack *S);

#endif
