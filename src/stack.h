#ifndef STACK_H
#define STACK_H

#define STACK_MAX_SIZE 512

typedef struct
{
    Operand v[STACK_MAX_SIZE];
    int top;
} Stack;

void push(Stack *S, Operand val);
Operand pop(Stack *S);
void init(Stack *S);

#endif
