#ifndef CODE_BOOK_H
#define CODE_BOOK_H

#define CD_A    0b000
#define CD_C    0b001
#define CD_G    0b010
#define CD_T    0b011
#define CD_N    0b100
#define CD_E    0b101 // end of line
#define CD_O    0b111 // others

const unsigned int CodeBook[60] = \
/*  A     B     C     D     E,    F,    G     H     I     J     K     L     M     N     O     P     Q     R     S     T     U     V     W     X     Y     Z */ \
{CD_A, CD_O, CD_C, CD_O, CD_O, CD_O, CD_G, CD_O, CD_O, CD_O, CD_O, CD_O, CD_O, CD_N, CD_O, CD_O, CD_O, CD_O, CD_O, CD_T, CD_O, CD_O, CD_O, CD_O, CD_O, CD_O,
/*  [      \     ]     ^     _     `  */
CD_O,  CD_O, CD_O, CD_O, CD_O, CD_O,
/*  a     b     c     d     e,    f,    g     h     i     j     k     l     m     n     o     p     q     r     s     t     u     v     w     x     y     z */
CD_A,  CD_O, CD_C, CD_O, CD_O, CD_O, CD_G, CD_O, CD_O, CD_O, CD_O, CD_O, CD_O, CD_N, CD_O, CD_O, CD_O, CD_O, CD_O, CD_T, CD_O, CD_O, CD_O, CD_O, CD_O, CD_O
};
#endif