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

#define fibonacci(AMOUNT) {                              \
    LOADI(COUNT, AMOUNT),                                \
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
      JMPBC(8),                                          \
      HALT()                                             \
    }

#define A 0
#define B 1
#define C 2
/* simple example with procedures */
#define procedures() {                          \
    LOADI(A,777),                               \
      LOADI(B, 888),                            \
      LOADI(C,999),                             \
      PRINT(A),                                 \
      CALL(9),                                  \
      PRINT(B),                                 \
      CALL(9),                                  \
      PRINT(C),                                 \
      RET(),                                    \
  /* beginning of procedure1 */                 \
    LOADI(A, 0),                                \
      LOADI(B, 1),                              \
      LOADI(C, 2),                              \
      PRINT(A),                                 \
      PRINT(B),                                 \
      PRINT(C),                                 \
      RET()                                     \
    }

#endif
