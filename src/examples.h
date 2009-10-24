#ifndef EXAMPLES_H
#define EXAMPLES_H

#define example1() {                            \
    LOADI(10, 0),                               \
      LOADI(5, 1),                              \
      MUL(0, 1),                                \
      PUSH(1),                                  \
      LOADI(3, 1),                              \
      MUL(0, 1),                                \
      POP(1),                                   \
      PRINT(0),                                 \
      PRINT(1),                                 \
      HALT()                                    \
    }


/* define some names for registers */
#define FIBN2 0
#define FIBN1 1
#define COUNT 2
#define ZERO 13
#define TMP 14
#define POINTER 15

#define fibonacci() {                                    \
    LOADI(COUNT, 14),                                    \
      LOADI(ZERO, 0),                                    \
      LOADI(FIBN2, 0),                                   \
      LOADI(FIBN1, 1),                                   \
      LOADI(POINTER, 0),                                 \
      ST(POINTER, FIBN2),                                \
      INC(POINTER),                                      \
      DEC(COUNT),                                        \
      ST(POINTER, FIBN1),                                \
      DEC(COUNT),                                        \
      INC(POINTER),                                      \
      /* loop starts here */                             \
      MOV(TMP, FIBN2),                                   \
      ADD(TMP, FIBN1),                                   \
      ST(POINTER, TMP),                                  \
      INC(POINTER),                                      \
      MOV(FIBN2, FIBN1),                                 \
      MOV(FIBN1, TMP),                                   \
      DEC(COUNT),                                        \
      NEQ(COUNT, ZERO),                                  \
      JMPBC(9),                                          \
      HALT()                                             \
    }
#endif
