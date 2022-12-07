#ifndef _BOARD_H
#define _BOARD_H

#include <unordered_map>
#include <string>
#include <stack>

#include "move.h"
#include "utils.h"

class Board{
  public:
    //array of bitboards for each piece
    bitboard boards[12];
    //tells whoose move it is 0=white 1=black
    Side to_move;

    //these vars track each kings ability to castle
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

    //LIFO stack to track all moves made
    std::stack<Board*> game;

    //contructors
    //contruct a copy of the current board
    //src - previous board passed by reference
    Board(const Board *src);

    //construct a board from a previous board then move
    // src - previous board, passed by reference
    // m - move to be made
    Board(const Board &src, Move m);

    //construct a board from a fen string
    //fen - fen string to construct the board
    Board(std::string fen);

    //default constructor
    Board() = default;

    //update a board state to reflect the given move
    //m - move to be made
    void make_move(Move m);

    //update a board to undo the previous move
    void undo_move();

    //checks if a position is valid
    //  attacked_squares -> all the attacking squares of the opposite color.
    bool is_valid(bitboard attacked_squares);

    //promote a pawn on the eigth rank to the given piece
    //pawn - the pawn type to be promoted
    //promotion - the type of new piece
    //square - the square the promotion occurs
    void promote(Piece pawn, Piece promotion, bitboard square);

    //set en_passant to targetsq
    //must be called after make_move, otherwise it will get reset
    void set_en_passant(bitboard targetsq);
    
    //printing functions
    void printBoard();
};


#endif
