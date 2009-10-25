#include "includes.h"

void push(Stack *S, Operand val)
{
  S->v[ S->top ] = val;
  (S->top)++;
}

Operand pop(Stack *S)
{
  (S->top)--;
  if(S->top <= 0) {
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
  return (S->top >= STACK_MAX_SIZE);
}

Bool empty(Stack *S)
{
  return (S->top <= 0);
}
