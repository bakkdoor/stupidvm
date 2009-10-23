#include "includes.h"

void push(Stack *S, Operand val)
{
    S->v[ S->top ] = val; 
   (S->top)++;    
/*  Equivalent to: S->v[ (S->top)++ ] = val;   */
}

Operand pop(Stack *S)
{
    (S->top)--;
    return (S->v[S->top]);
/*  Equivalent to: return (S->v[--(S->top)]);  */
}

void init(Stack *S)
{
    S->top = 0;
}

int full(Stack *S)
{
    return (S->top >= STACK_MAX_SIZE);
}

