/*
  Author: Zachary Talarick
  Date: 05/26/21
  Implements functions to generate all legal moves from a given position
  the moveList is represented as a vector of Boards
  it generates a list of all positions that can be reached by one legal move

  TODO:
    -movegen function
    -quiescence list (list of quiet moves)
    -special gen function for when in check
    -Perft testing function
*/

#include <iostream>

#include "movegen.h"

using namespace std;

//for now generate psudeolegal moves
//TODO consider making a new class/struct Move containing only the information
//necessary to make the move and not the entire board state
//TODO generate only legal moves
//TODO Check edges of board
//TODO FIX MOVEGEN FOR MORE THAN TWO PIECES WITH PAWN PROMOTIONS
//TODO should change this to pass by reference as well
vector<Board> movegen(Board pos){
  //iterate every piece type that can move
  //use the fancy inline if statement to evaluate i to the correct indices
  vector<Board> moveList;
  for(int i = (pos.to_move ? 0 : 6); i < (pos.to_move ? 6 : 12); i = i + 1){
    Piece p = static_cast<Piece>(i);
    if(p == wking || p == bking){
      gen_king_moves(moveList, pos, p);
    }

    if(p == wqueen || p == bqueen){

    }
    if(p == wknight || p == bknight){
      gen_knight_moves(moveList, pos, p);
    }
    if(p == wbishop || p == bbishop){

    }
    if(p == wrook || p == brook){

    }
    if(p == wpawn || p == bpawn){

    }
  }
  return moveList;
}

//function to add the generated king moves to the moveList
//moveList passed by reference
//board passed by reference
//TODO function to check position if king is in check
void gen_king_moves(vector<Board> &moveList, const Board &pos, Piece p){
      bitboard ally_board = pos.to_move ? pos.black_pieces : pos.white_pieces;

      if(no_ally_piece(ally_board, pos.boards[p] >> 1) &&
      !(pos.boards[p] & 72340172838076673ULL)) //not in h file
        moveList.push_back(Board(pos, p, pos.boards[p] >> 1)); //move 1 east

      if(no_ally_piece(ally_board, pos.boards[p] << 1) && 
        !(pos.boards[p] & 9259542123273814144ULL)) //check that the king is not on the A file
        moveList.push_back(Board(pos, p, pos.boards[p] << 1)); //move 1 west

      if(no_ally_piece(ally_board, pos.boards[p] >> 8) &&
       !(pos.boards[p] & 255ULL)) //not on 1st rank
        moveList.push_back(Board(pos, p, pos.boards[p] >> 8)); //move 1 south

      if(no_ally_piece(ally_board, pos.boards[p] << 8) &&
       !(pos.boards[p] & 18374686479671623680ULL)) //not on 8th rank
        moveList.push_back(Board(pos, p, pos.boards[p] << 8)); //move 1 north

      if(no_ally_piece(ally_board, pos.boards[p] << 7) &&
       !(pos.boards[p] & 18374969058471772417ULL)) //not in h file for 8th rank
        moveList.push_back(Board(pos, p, pos.boards[p] << 7)); //move 1 ne

      if(no_ally_piece(ally_board, pos.boards[p] << 9) &&
      !(pos.boards[p] & 18410856566090662016ULL)) //not in a file or 8th rank
        moveList.push_back(Board(pos, p, pos.boards[p] << 9)); //move 1 nw

      if(no_ally_piece(ally_board, pos.boards[p] >> 7) &&
      !(pos.boards[p] & 9259542123273814271ULL)) //not in a file or 1st rank
        moveList.push_back(Board(pos, p, pos.boards[p] >> 7)); //move 1 sw

      if(no_ally_piece(ally_board, pos.boards[p] >> 9) &&
      !(pos.boards[p] & 72340172838076927ULL)) //not in h file or 1st rank
        moveList.push_back(Board(pos, p, pos.boards[p] >> 9)); //move 1 se
}

//function to generate and add all legal knight moves to the moveList
//moveList and board passed by reference
void gen_knight_moves(vector<Board> &moveList, const Board &pos, Piece p){
    //calculate the ally pieces
    bitboard ally_board = pos.to_move ? pos.black_pieces : pos.white_pieces;

    // the knights are multiple pieces stored on the same bitboard
    // here I seperate the two pieces and generate moves for them both
    bitboard all_knights = pos.boards[p];
    //this vector will hold the seperate bitboards for each knight
    //need to do it this way because we need the original square for the other knight
    // when adding the moves to the moveList
    //size 10 because 2 starting knights and 8 possible pawn promotions
    vector<bitboard> sep_knights(10);
    separate_bits(sep_knights, all_knights);
 
    //now generate the moves for each knight
    /* 
      Possible moves: 
      >> 6  - bounds check for A and B file, 1st rank
      << 6  - bounds check for G and H file, 8th rank
      >> 10 - bounds check for G and H file, 1st rank
      << 10 - bounds check for A and B file, 8th rank
      >> 15 - bounds check for A file, 1st and 2nd rank
      << 15 - bounds check for H file, 7th and 8th rank
      >> 17 - bounds check for H file, 1st and 2nd rank
      << 17 - bounds check for A file, 7th and 8th rank
    */
    for(int curr_kn = 0; curr_kn < 10; curr_kn++){
      if(sep_knights.at(curr_kn)){ // if there is a knight at this index

        bitboard curr_move = sep_knights.at(curr_kn) >> 6;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 13889313184910721279ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) << 6;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 18375534216072069891ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) >> 10;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 217020518514230271ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) << 10;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 18428941609300181184ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) >> 15;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 9259542123273846783ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) << 15;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 18446463702556279041ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) >> 17;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 72340172838141951ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));

        curr_move = sep_knights.at(curr_kn) << 17;
        if(no_ally_piece(ally_board, curr_move) && !(sep_knights.at(curr_kn) & 18446603888132915328ULL))
          moveList.push_back(Board(pos, p, combine_bits(sep_knights, curr_move, sep_knights.at(curr_kn))));
      } else{
        break; //if you reach an index with no knight you can stop the loop
      }
    }
}

bool no_ally_piece (bitboard ally_pieces, bitboard move){

  // cout << "Ally Pieces: " << ally_pieces << endl;
  // cout << "Move: " << move << endl;
  // cout << "AP & M: " << (ally_pieces & move) << endl << endl;

  return (ally_pieces & move) == 0;
}

//This function seperates each bit into a seperate 
void separate_bits(vector<bitboard> &bits, bitboard board){
  int it = 0;
  while (board){
    cout << "Board: " << board << endl;
    cout << "It: " << it << endl;
    bits.at(it) = (board & -board);
    it++;
    board &= board - 1ULL;
  }
}

//this function combines a vector of 1 bit bitboards into 1 to be stored
// old_piece is the piece you do not want to be combined,
bitboard combine_bits(vector<bitboard> &bits, bitboard move, bitboard old_piece){
  int size = bits.size();
  for(int i = 0; i < size; i++){
    if(bits.at(i)){
      if(bits.at(i) != old_piece){
        move |= bits.at(i);
      }
    }else{
      break; //can break if a 0 is reached
    }
  }
  return move;
}

//TODO do this function, maybe by calling generate moves?
bitboard gen_attacked_squares(Board pos, Side side, bool king){
  return 0;
}
