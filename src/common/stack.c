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

void st_push(Stack *S, Operand val)
{
  S->values[ S->top ] = val;
  (S->top)++;
}

Operand st_pop(Stack *S)
{
  (S->top)--;
  if(S->top < 0) {
    fprintf(stderr, "\nERROR: pop() on empty Stack!\n");
    exit(-1);
  } else {
    return (S->values[S->top]);
  }
}

Stack* st_init(void)
{
  return st_init_size(STACK_DEFAULT_SIZE);
}

Stack* st_init_size(int size) 
{
  Stack *s = malloc(sizeof(Stack));
  s->values = malloc(sizeof(Operand) * size);
  s->top = 0;
  s->size = size;
  return s;
}

Bool st_full(Stack *S)
{
  return (S->top > S->size);
}

Bool st_empty(Stack *S)
{
  return (S->top <= 0);
}
