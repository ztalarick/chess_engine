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
*/

/*
  TODO:
    1. investigate bug with move clock counter
    2. try to figure out a way to fix the game stack type or put it on the heap
*/

#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <vector>

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

Board::Board(const Board *src){
  std::copy(src->boards, src->boards + 12, boards);
  to_move = src->to_move;
  white_pieces = src->white_pieces;
  black_pieces = src->black_pieces;
  wk_castle = src->wk_castle;
  wq_castle = src->wq_castle;
  bk_castle = src->bk_castle;
  bq_castle = src->bq_castle;
  en_passant = src->en_passant;
  half_clock = src->half_clock;
  full_count = src->full_count;
  game = src->game;
}

//contructor to make a copy of a board and make the given move
Board::Board(const Board &src, Move m){
  std::copy(src.boards, src.boards + 12, boards);
  to_move = src.to_move;
  white_pieces = src.white_pieces;
  black_pieces = src.black_pieces;
  wk_castle = src.wk_castle;
  wq_castle = src.wq_castle;
  bk_castle = src.bk_castle;
  bq_castle = src.bq_castle;
  en_passant = src.en_passant;
  half_clock = src.half_clock;
  full_count = src.full_count;
  game = src.game;

  this->make_move(m);
}

//The Constructor will take a fen string then initialize the bitboard array
Board::Board(string fen){
  game = stack<Board*>();
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

  //castling ability
  wk_castle = false;
  wq_castle = false;
  bk_castle = false;
  bq_castle = false;
  
  for(auto &ch : fen_parts[2]){
    if(ch == 'K'){
      wk_castle = true;
    }else if(ch == 'Q'){
      wq_castle = true;
    } else if(ch == 'k'){
      bk_castle = true;
    } else if(ch == 'q'){
      bq_castle = true;
    }
  }

  //En passant
  if(fen_parts[3].compare("-") != 0){
    unordered_map<string, bitboard> en_passant_map = { {"a3", 8388608ULL}, {"b3", 4194304ULL}, 
    {"c3", 2097152ULL}, {"d3", 1048576ULL}, {"e3", 524288ULL}, {"f3", 262144ULL}, {"g3", 131072ULL}, {"h3", 65536ULL},
    {"a6", 140737488355328ULL}, {"b6", 70368744177664ULL}, {"c6", 35184372088832ULL}, {"d6", 17592186044416ULL}, {"e6", 8796093022208ULL}, {"f6", 4398046511104ULL}, {"g6", 2199023255552ULL}, {"h6", 1099511627776ULL} };

    en_passant = en_passant_map[fen_parts[3]];
  }else{
    en_passant = 0;
  }

  half_clock = stoi(fen_parts[4]);
  full_count = stoi(fen_parts[5]);

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

void Board::make_move(Move m){
  //create a copy of the current position before the move
  static Board prev = Board(this);
  //add to stack
  game.push(&prev);

  boards[m.p] = m.move;
  
  //handling promotion
  if((m.p == wpawn && m.move & 18374686479671623680ULL) || (m.p == bpawn && m.move & 255ULL)){
    promote(m.p, m.promote, m.move);
  }

  if(((to_move == white) && (black_pieces & m.move))){ // capture
    half_clock = 0; //reset half clock
    for(int i = 6; i < 12; i++){ //iterate through all enemy pieces
      boards[i] = boards[i] & m.move ? (boards[i] ^ m.move) : boards[i]; //remove the bits that are set on the move square
    }
  } else if((to_move == black) && (white_pieces & m.move)){ //same for black side
    half_clock = 0; //reset half clock
    for(int i = 0; i < 6; i++){ //iterate through all enemy pieces
       boards[i] = boards[i] & m.move ? (boards[i] ^ m.move) : boards[i]; //remove the bits that are set on the move square
    }
  } else if((to_move == white) && (m.move & en_passant)){//en passant and white move
    half_clock = 0; //reset half clock
    bitboard pawn_to_remove = en_passant >> 8;
    boards[bpawn] = boards[bpawn] ^ pawn_to_remove; //exclusive or
  }else if((to_move == black) && (m.move & en_passant)){ // en passant and black move
    half_clock = 0; //reset half clock
    bitboard pawn_to_remove = en_passant << 8;
    boards[wpawn] = boards[wpawn] ^ pawn_to_remove; 

  }else if(m.p == wpawn || m.p == bpawn){ //reset half clock if pawn move
    half_clock = 0;
    }else{
      half_clock++;
    }
  if(to_move == black){ //increment fullmove counter when black moves
    full_count++; //TODO something messed up here.
  }
  to_move = to_move ? white : black; //switch side to_move

  //handle en passant
  if(m.en_passant){
    set_en_passant(m.en_passant);
  }else{
    set_en_passant(0); //reset en_passant square
  }
  //update white/black piece variables - this might be kinda slow perhaps theres a faster way
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

//TODO
void Board::undo_move(){
  Board* prev = game.top();
  game.pop();
  std::copy(prev->boards, prev->boards + 12, boards);
  to_move = prev->to_move;
  white_pieces = prev->white_pieces;
  black_pieces = prev->black_pieces;
  wk_castle = prev->wk_castle;
  wq_castle = prev->wq_castle;
  bk_castle = prev->bk_castle;
  bq_castle = prev->bq_castle;
  en_passant = prev->en_passant;
  half_clock = prev->half_clock;
  full_count = prev->full_count;
  return;
}

void Board::promote(Piece pawn, Piece promotion, bitboard square){
  boards[promotion] = square | boards[promotion]; //add the promoted piece to the appropriate square
  boards[pawn] = square ^ boards[pawn];         //get rid of the old pawn
  
  //update the white/black piece variables
  for(int i = 0; i < 12; i++){
    if(i < 6){//white bitboard
      white_pieces = boards[i] | white_pieces;
    }else { //black bitboard
      black_pieces = boards[i] | black_pieces;
    }
  }
}

//sets the en_passant square to the targetsq
//must be called after make move, otherwise it will be reset
void Board::set_en_passant(bitboard targetsq){
  en_passant = targetsq;
}

void Board::printBitboard(bitboard b){
  vector<bitboard> squares;
  for(int j = 1; j < 65; j++){
    squares.push_back( (b & 1) );
  //   cout << (b & 1) << ((j % 8 == 0) ? '\n' : ' ');
    b = b >> 1;
  }
  reverse(squares.begin(), squares.end());
  for(int j = 1; j < 65; j++){
    cout << squares.at(j - 1) << ((j % 8 == 0) ? '\n' : ' ');
  }
}

void Board::printBoard(){
  unordered_map<int,string> pieces = { {0, "white king"}, {1, "white queen"}, {2, "white knight"}, {3, "white bishop"}, {4, "white rook"}, {5, "white pawn"},
    {6, "black king"}, {7, "black queen"}, {8, "black knight"}, {9, "black bishop"}, {10, "black rook"}, {11, "black pawn"} };

  cout << "Side to move: " << (to_move ? "Black" : "White") << endl;
  cout << endl << "Bitboards: " << endl;
  for(int i = 0; i < 12; i++){
    cout << "Bitboard " << pieces.at(i) << ": " << boards[i] << endl;

    printBitboard(boards[i]);

  cout << endl;

  }

  cout << "White Pieces: " << white_pieces << endl;
  printBitboard(white_pieces);
  cout << endl;

  cout << "Black Pieces: " << black_pieces << endl;
  printBitboard(black_pieces);
  cout << endl;

  cout << "Castling Ability: " << "WK - " << wk_castle 
  << " WQ - " << wq_castle << " BK - " << bk_castle << " BQ - " << bq_castle << endl;
  cout << "En Passant: " << en_passant << endl;
  cout << "Halfmove Clock: " << half_clock << endl;
  cout << "Fullmove Counter: " << full_count << endl;

  cout << " __________________" << endl;
}
