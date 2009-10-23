#include "includes.h"

void push(Stack *S, OPERAND val)
{
    S->v[ S->top ] = val; 
   (S->top)++;    
/*  Equivalent to: S->v[ (S->top)++ ] = val;   */
}

OPERAND pop(Stack *S)
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

