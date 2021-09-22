#ifndef _BOARD_H
#define _BOARD_H

typedef unsigned long long bitboard;
const bitboard universe = 0xffffffffffffffffULL;

enum Piece {wking, wqueen, wknight, wbishop, wrook, wpawn,
   bking, bqueen, bknight, bbishop, brook, bpawn};

enum Side {white, black};

#include <unordered_map>
#include <string>

class Board{
  public:
    //array of bitboards for each piece
    bitboard boards[12];
    //tells whoose move it is
    Side to_move;

    //these vars track the each kings ability to castle
    bool wk_castle; //white kingside
    bool wq_castle; //white queenside
    bool bk_castle; //black kingside
    bool bq_castle; //black queenside


    //these are 2 bitboards that track all of the pieces for a particular side
    //useful for movegeneration
    bitboard white_pieces;
    bitboard black_pieces;

    //these 2 are counters for how many moves it has been
    int half_clock; //tracks the 50 move rule, reset to 0 for a capture or pawn move, increment otherwise
    int full_count; //increment every black move

    //tracks the target squares after a double pawn move for en passant
    bitboard en_passant;

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

    //promote a pawn on the eigth rank to the given piece
    //pawn - the pawn type to be promoted
    //promotion - the type of new piece
    //square - the square the promotion occurs
    void promote(Piece pawn, Piece promotion, bitboard square);

    friend void test();
    void printBoard();
};


#endif
