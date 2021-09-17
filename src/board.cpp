/*
  Author: Zachary Talarick
  Date: 03/29/2021

  This file provides a class to implement a chess board

  https://www.chessprogramming.org/Bitboards
  https://gekomad.github.io/Cinnamon/BitboardCalculator/

  Each pieces location is stored as a bitboard, a 64 bit variable with:
    1 = piece present
    0 = piece absent
  1 bit = 1 square on the chess board
  1 bitboard for each type of piece and color:
    White/Black:
      -King
      -Queen
      -Knight
      -Bishop
      -Rook
      -Pawn
  12 total bitboards

  TODO:
    -finish the contructor to get all information out of a FEN string
    - represent the 50 move rule
    - en passant
    - castling
*/

#include <iostream>
#include <unordered_map>
#include <ctype.h>
#include <algorithm>

#include "board.h"

using namespace std;


//this function is to split a fen string by a delimeter
//may move this to another file?
void split(string* arr, string s, string delimeter){
  size_t pos = 0;
  int array_index = 0;
  string token;
  while ((pos = s.find(delimeter)) != std::string::npos) {
    token = s.substr(0, pos);
    arr[array_index] = token;
    array_index++;
    s.erase(0, pos + delimeter.length());
  }
  arr[array_index] = s;
}

//contructor to make a copy of a board and make the given move
Board::Board(const Board &src, Piece p, bitboard move){
  std::copy(src.boards, src.boards + 12, boards);
  to_move = src.to_move;
  white_pieces = 0;
  black_pieces = 0;
  this->make_move(p, move);
}

//The Constructor will take a fen string then initialize the bitboard array
Board::Board(string fen){
  //initialize every board to 0
  for(int i = 0; i < 12; i++){
    boards[i] = 0;
  }
  //map to get the index of the Boards array
  unordered_map<char, Piece> map = { {'K', wking}, {'Q', wqueen}, {'N', wknight}, {'B', wbishop}, {'R', wrook}, {'P', wpawn},
    {'k', bking}, {'q', bqueen}, {'n', bknight}, {'b', bbishop}, {'r', brook}, {'p', bpawn} };
  string fen_parts[6];
  string fen_board[8];
  split(fen_parts, fen, " "); //first split the fen by spaces
  split(fen_board, fen_parts[0], "/"); //split by row
  Piece piece_type;
  bitboard board = 9223372036854775808ULL; //this number is the bitboard representing 1 bit in the square A8

  for(const string &s : fen_board){ //build bitboards from fen_board
    for(auto &c : s){
      if(isdigit(c)){//s empty squares
        board = board >> (c - '0'); //shift the board by s (converted to int)
      }else{ //s is a char representing a piece
        piece_type = map[c];
        boards[piece_type] = boards[piece_type] | board; //use or since there are multiple i.e. rooks being stored on the rook bitboard
        board = board >> 1; //shift the bit over one for the next bit
      }
    }
  }

  to_move = (fen_parts[1].compare("w") == 0) ? white : black; //white or black to move

  //generate white_pieces and black_pieces
  white_pieces = 0;
  black_pieces = 0;
  for(int i = 0; i < 12; i++){
    if(i < 6){//white bitboard
      white_pieces = boards[i] | white_pieces;
    }else { //black bitboard
      black_pieces = boards[i] | black_pieces;
    }
  }
}

void Board::make_move(Piece p, bitboard move){
  boards[p] = move;
  to_move = to_move ? white : black;

  //update white/black piece variables - this might be kinda slow perhaps theres a faster way
  for(int i = 0; i < 12; i++){
    if(i < 6){//white bitboard
      white_pieces = boards[i] | white_pieces;
    }else { //black bitboard
      black_pieces = boards[i] | black_pieces;
    }
  }
}

void Board::promote(Piece pawn, Piece promotion, bitboard square){
  boards[promotion] = square & boards[promotion]; //add the promoted piece to the appropriate square
  boards[pawn] = !(square & boards[pawn]);         //get rid of the old pawn
  
  //update the white/black piece variables
  for(int i = 0; i < 12; i++){
    if(i < 6){//white bitboard
      white_pieces = boards[i] | white_pieces;
    }else { //black bitboard
      black_pieces = boards[i] | black_pieces;
    }
  }
}


void Board::printBoard(){
  cout << "Side to move: " << (to_move ? "Black" : "White") << endl;
  cout << endl << "Bitboards: " << endl;
  for(int i = 0; i < 12; i++){
    cout << "Bitboard " << i << ": " << boards[i] << endl;
  }

  cout << "White Pieces: " << white_pieces << endl;
  cout << "Black Pieces: " << black_pieces << endl;

  cout << " __________________" << endl;
}
