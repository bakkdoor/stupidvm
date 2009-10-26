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

void push(Stack *S, Operand val)
{
  S->v[ S->top ] = val;
  (S->top)++;
}

Operand pop(Stack *S)
{
  (S->top)--;
  if(S->top < 0) {
    fprintf(stderr, "\nERROR: pop() on empty Stack!\n");
    exit(-1);
  } else {
    return (S->v[S->top]);
  }
}

void init(Stack *S)
{
  S->top = 0;
}

Bool full(Stack *S)
{
  return (S->top > STACK_MAX_SIZE);
}

Bool empty(Stack *S)
{
  return (S->top <= 0);
}
