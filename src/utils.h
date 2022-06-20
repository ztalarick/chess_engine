#ifndef _UTILS_H
#define  _UTILS_H

typedef unsigned long long bitboard;
const bitboard universe = 0xffffffffffffffffULL;

enum Piece {wking, wqueen, wknight, wbishop, wrook, wpawn,
   bking, bqueen, bknight, bbishop, brook, bpawn};

enum Side {white, black};

#endif