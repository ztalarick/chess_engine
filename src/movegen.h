#ifndef _MOVEGEN_H
#define  _MOVEGEN_H

#include <vector>
#include "board.h"

// function to generate all legal moves from a given position
// return - a vector of board states containg every legal branching board state
// pos - the start position
// moveList - vector containing the moves, passed by reference
std::vector<Board> movegen(std::vector<Board> &moveList, Board pos);

//checks if an ally piece exists in the square you want to move too
// ally_pieces - a bitboard with a bitset for all allied pieces
// move - a bitboard with the square set that you want ot move to
// return - true if no allied piece on that square, false otherwise
bool no_ally_piece (bitboard ally_pieces, bitboard move);

//seperates a bitboard with multiple pieces into an array
//the bits array is size 10 (9 for queen)
// because there is a total possibility of 10 of one piece
// 2 starting and 8 pawn promotions 
//bits - the vector containg the seperated bits, passed by reference.
//board - the bitboard with multiple pieces you want to seperate. 
void separate_bits(std::vector<bitboard> &bits, bitboard board);

//combines seperated bits into a single bitboard for storage in a Board position
// bits - the vector containg the one bit pieces to combine, passed by reference
// move - the new move you want to combine with - set to 0 if no move
// old_piece - the piece you do not want to be combined - set to 0 to combine all
bitboard combine_bits(std::vector<bitboard> &bits, bitboard move, bitboard old_piece);

//generates attaked squares
//king boolean decides if to include the king in the calculation
//used for generating legal king moves
bitboard gen_attacked_squares(Board pos, Side side, bool king);

//functions to generate and add all legal moves to the moveList by piece
//moveList - a vector of board positions that contain the boardstate after a move, passed by reference
//pos - current position you want to generate moves for, passed by reference
//p - the piece you want to generate for
void gen_king_moves(std::vector<Board> &moveList, const Board &pos, Piece p);
void gen_knight_moves(std::vector<Board> &moveList, const Board &pos, Piece p);
void gen_pawn_moves(std::vector<Board> &moveList, const Board &pos, Piece p);
void gen_rook_moves(std::vector<Board> &moveList, const Board &pos, Piece p);
void gen_bishop_moves(std::vector<Board> &moveList, const Board &pos, Piece p);

#endif
