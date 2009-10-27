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
      HALT(),                                   \
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
