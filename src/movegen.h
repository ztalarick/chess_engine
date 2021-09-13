#ifndef _MOVEGEN_H
#define  _MOVEGEN_H

#include <vector>
#include "board.h"
std::vector<Board> movegen(Board pos);

//checks if an ally piece exists in the square you want to move too
bool no_ally_piece (bitboard ally_pieces, bitboard move);

//generates attaked squares
//king boolean decides if to include the king in the calculation
//used for generating legal king moves
bitboard gen_attacked_squares(Board pos, Side side, bool king);

//functions to generate and add all legal moves to the moveList by piece
void gen_king_moves(std::vector<Board> &moveList, const Board &pos, Piece p);
void gen_knight_moves(std::vector<Board> &moveList, const Board &pos, Piece p);

#endif
