#ifndef _UTILS_H
#define  _UTILS_H

#include <string>

typedef unsigned long long bitboard;
const bitboard universe = 0xffffffffffffffffULL;

enum Piece {wking, wqueen, wknight, wbishop, wrook, wpawn,
   bking, bqueen, bknight, bbishop, brook, bpawn, none};

enum Side {white, black};

enum Castle {wk, wq, bk, bq, not_castle};

const std::string CastleTypes[] = {"white kingside castle", "white queenside castle", "black kingside castle", "black queenside castle", "no castle"};
const std::string PieceTypes[] = {"wking", "wqueen", "wknight", "wbishop", "wrook", "wpawn",
   "bking", "bqueen", "bknight", "bbishop", "brook", "bpawn", "none"};
const std::string SideTypes[] = {"white", "black"};
//prints a bitboard
void printBitboard(bitboard b);

//splits a given string by the given delimeter
void split(std::string* arr, std::string s, std::string delimeter);


#endif