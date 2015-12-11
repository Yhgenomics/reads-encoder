// Copyright (c) 2015 Yhgenomics. All rights reserved.
// Description: Code Book 
// Creator: Ke Yang
// Date: 2015/12/9

#ifndef CODE_BOOK_H
#define CODE_BOOK_H

#define CD_A    0b000
#define CD_C    0b001
#define CD_G    0b010
#define CD_T    0b011
#define CD_N    0b100
#define CD_E    0b101 // end of line
#define CD_F    0b111 // others

const unsigned  char    ALL1         = 0b11111111;
const unsigned  int     BlockSize    = 64;
const unsigned  char    CodeBook[60] = \
/*  A     B     C     D     E,    F,    G     H     I     J     K     L     M     N     O     P     Q     R     S     T     U     V     W     X     Y     Z */ \
{CD_A, CD_F, CD_C, CD_F, CD_E, CD_F, CD_G, CD_F, CD_F, CD_F, CD_F, CD_F, CD_F, CD_N, CD_F, CD_F, CD_F, CD_F, CD_F, CD_T, CD_F, CD_F, CD_F, CD_F, CD_F, CD_F,
/*  [      \     ]     ^     _     `  */
CD_F,  CD_F, CD_F, CD_F, CD_F, CD_F,
/*  a     b     c     d     e,    f,    g     h     i     j     k     l     m     n     o     p     q     r     s     t     u     v     w     x     y     z */
CD_A,  CD_F, CD_C, CD_F, CD_E, CD_F, CD_G, CD_F, CD_F, CD_F, CD_F, CD_F, CD_F, CD_N, CD_F, CD_F, CD_F, CD_F, CD_F, CD_T, CD_F, CD_F, CD_F, CD_F, CD_F, CD_F
};

#endif