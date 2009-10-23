#include "includes.h"

/**
   Build up a command from opcode and two operands.
*/
Command command(Opcode opcode, Operand op1, Operand op2) {
  Command c;

  /* strip of first 3 bits of operands */
  op1 = (op1 << 3) >> 3;
  op2  = (op2 << 3) >> 3;
  
  /* now, lets create the command */
  c = opcode;
  c <<= OP_SIZE;
  c |= op1;
  c <<= OP_SIZE;
  c |= op2;
  return c;
}
