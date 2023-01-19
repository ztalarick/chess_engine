/*
  Author: Zachary Talarick
  Date: 06/08/22
  A class to represent a move
*/

#include <iostream>

#include "move.h"

using namespace std;

Move::Move(bitboard move, bitboard prev, Piece p){
    this->move = move;
    this->prev = prev;
    this->p = p;
    this->en_passant = false;
    this->promote = none;
    this->castle_type = not_castle;
}

Move::Move(bitboard move, bitboard prev, Piece p, bitboard en_passant){
    this->move = move;
    this->prev = prev;
    this->p = p;
    this->en_passant = en_passant;
    this->promote = none;
    this->castle_type = not_castle;
}

Move::Move(bitboard move, bitboard prev, Piece p, Piece promote){
  this->move = move;
  this->prev = prev;
  this->p = p;
  this->promote = promote;
  this->en_passant = false;
  this->castle_type = not_castle;
}

Move::Move(Castle castle_type){
  this->castle_type = castle_type;
  this->move = 0;
  this->prev = 0;
  this->en_passant = false;
  this->promote = none;

  if(castle_type == wk || castle_type == wq)
    this->p = wking;

  if(castle_type == bk || castle_type == bq)
    this->p = bking;

  if(castle_type == not_castle)
    this->p = none;
}

void Move::print_move(){
  cout << "move: " << move << endl;
  printBitboard(move);
  cout << endl << "prev: " << prev << endl;
  printBitboard(prev);
  cout << endl << "piece: " << PieceTypes[p] << endl;
  cout << "promote: "     << PieceTypes[promote] << endl;
  cout << "en_passant: "  << en_passant  << endl;
  cout << "castle_type: " << CastleTypes[castle_type] << endl;
}