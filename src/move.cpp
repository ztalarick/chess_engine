/*
  Author: Zachary Talarick
  Date: 06/08/22
  A class to represent a move
*/

#include <iostream>
#include <string>

#include "move.h"

using namespace std;

Move::Move(bitboard move, Piece p){
    this->move = move;
    this->p = p;
    this->en_passant = false;
    this->promote = none;
}

Move::Move(bitboard move, Piece p, bitboard en_passant){
    this->move = move;
    this->p = p;
    this->en_passant = en_passant;
    this->promote = none;
}

Move::Move(bitboard move, Piece p, Piece promote){
  this->move = move;
  this->p = p;
  this->promote = promote;
  this->en_passant = false;
}

void Move::print_move(){
  cout << "move: " << move << endl;
  cout << "piece: " << p << endl;
  cout << "promote: " << promote << endl;
  cout << "en_passant: " << en_passant << endl;
}