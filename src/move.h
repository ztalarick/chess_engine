#ifndef _MOVE_H
#define  _MOVE_H

#include "utils.h"

//This class tracks the information needed to make a move given an initial position
class Move{
    public:
    //contains 1 bit set with the square p is moving to
    bitboard move;

    //contains 1 bit set with the square p is moving from
    bitboard prev;

    //the piece to that is being moved.
    Piece p;

    //piece a pawn would promote to
    Piece promote;

    //Flag to indicate that this move would 
    bitboard en_passant;

    //indicates the type of castle or none
    Castle castle_type;

    //constructors
    Move(bitboard move, bitboard prev, Piece p, bitboard en_passant);
    Move(bitboard move, bitboard prev, Piece p, Piece promote);
    Move(bitboard move, bitboard prev, Piece p);
    Move(Castle castle_type);
    Move() = default;

    void print_move();
};

#endif