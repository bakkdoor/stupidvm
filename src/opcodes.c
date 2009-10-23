#include "includes.h"

OPERAND first_op(COMMAND c)
{
  COMMAND opcode_removed = c << OPC_SIZE;
  /* after opcode bits are removed, shift to right, until first operand is at right */
  return (opcode_removed >> (OPC_SIZE + OP_SIZE));
}

OPERAND second_op(COMMAND c)
{
  COMMAND opcode_removed = c << OPC_SIZE;
  /* now also remove first operand */
  opcode_removed <<= OP_SIZE;
  return (opcode_removed >> (OPC_SIZE + OP_SIZE));
}

/**
   Return the opcode for a given command.
   
   the opcode is made up of the first 5 bits within the 16 bits of the
   command
*/
OPCODE opcode(COMMAND c)
{
  return (c >> (COMMAND_SIZE - OPC_SIZE));
}


/**
   Build up a command from opcode and two operands.
*/
COMMAND command(OPCODE opcode, OPERAND op1, OPCODE op2)
{
  COMMAND c;

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
