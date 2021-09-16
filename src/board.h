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

    //contructors
    //construct a board from a previous board then move
    // src - previous board, passed by reference
    // p - piece that was moved
    // move - the bitboard updated with the move
    Board(const Board &src, Piece p, bitboard move);

    //construct a board from a fen string
    //fen - fen string to construct the board
    Board(std::string fen);

    //update a board state to reflect the given move
    //p - piece to be moved
    //move - the new bitboard with the updated move
    void make_move(Piece p, bitboard move);

    friend void test();
    void printBoard();
};


#endif
