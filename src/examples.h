#ifndef EXAMPLES_H
#define EXAMPLES_H

#define example1() {                           \
    LOADI(10, 0),                              \
      LOADI(5, 1),                            \
      MUL(0, 1),                               \
      PUSH(1),                              \
      LOADI(3, 1),                              \
      MUL(0, 1),                                \
      POP(1),                                \
      PRINT(0),                              \
      PRINT(1),                              \
      HALT()                                 \
    }

#endif
