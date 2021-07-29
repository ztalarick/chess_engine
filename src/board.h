#ifndef _BOARD_H
#define _BOARD_H


typedef unsigned long long bitboard;
const bitboard universe = 0xffffffffffffffffULL;

enum Piece {wking, wqueen, wknight, wbishop, wrook, wpawn,
   bking, bqueen, bknight, bbishop, brook, bpawn};

enum Side {white, black};

#include <string>



class Board{
  public:
    bitboard boards[12];
    Side to_move;

    //these are 2 bitboards that track all of the pieces for a particular side
    //useful for movegeneration
    bitboard white_pieces;
    bitboard black_pieces;

    Board(const Board &src, Piece p, bitboard move);
    Board(std::string fen);

    void make_move(Piece p, bitboard move);

    friend void test();
    void printBoard();
};


#endif
