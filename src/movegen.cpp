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

#include "movegen.h"

using namespace std;

//for now generate psudeolegal moves
//TODO consider making a new class/struct Move containing only the information
//necessary to make the move and not the entire board state
//TODO generate only legal moves
//TODO Check edges of board
//TODO FIX MOVEGEN FOR MORE THAN TWO PIECES WITH PAWN PROMOTIONS
vector<Board> movegen(Board pos){
  //iterate every piece type that can move
  //use the fancy inline if statement to evaluate i to the correct indices
  vector<Board> moveList;
  for(int i = (pos.to_move ? 0 : 6); i < (pos.to_move ? 6 : 12); i = i + 1){
    Piece p = static_cast<Piece>(i);
    // bitboard ally_board = pos.to_move ? pos.white_pieces : pos.black_pieces;
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
void gen_king_moves(vector<Board> &moveList, const Board &pos, Piece p){
      bitboard ally_board = pos.to_move ? pos.white_pieces : pos.black_pieces;


      //TODO function to check position if king is in check
      if(no_ally_piece(ally_board, pos.boards[p] >> 1))
        moveList.push_back(Board(pos, p, pos.boards[p] >> 1)); //move 1 east

      if(no_ally_piece(ally_board, pos.boards[p] << 1))
        moveList.push_back(Board(pos, p, pos.boards[p] << 1)); //move 1 west

      if(no_ally_piece(ally_board, pos.boards[p] << 8))
        moveList.push_back(Board(pos, p, pos.boards[p] << 8)); //move 1 south

      if(no_ally_piece(ally_board, pos.boards[p] >> 8))
        moveList.push_back(Board(pos, p, pos.boards[p] >> 8)); //move 1 north

      if(no_ally_piece(ally_board, pos.boards[p] >> 9))
        moveList.push_back(Board(pos, p, pos.boards[p] >> 9)); //move 1 ne

      if(no_ally_piece(ally_board, pos.boards[p] >> 7))
        moveList.push_back(Board(pos, p, pos.boards[p] >> 7)); //move 1 nw

      if(no_ally_piece(ally_board, pos.boards[p] << 9))
        moveList.push_back(Board(pos, p, pos.boards[p] << 9)); //move 1 sw

      if(no_ally_piece(ally_board, pos.boards[p] << 7))
        moveList.push_back(Board(pos, p, pos.boards[p] << 7)); //move 1 se
}

//function to generate and add all legal knight moves to the moveList
//moveList and board passed by reference
void gen_knight_moves(vector<Board> &moveList, const Board &pos, Piece p){
    //calculate the ally pieces
    bitboard ally_board = pos.to_move ? pos.white_pieces : pos.black_pieces;

    // the knights are two pieces stored on the same bitboard
    // here I seperate the two pieces and generate moves for them both
    bitboard two_knights = pos.boards[p];
    //this array will hold the seperate bitboards for each knight
    //need to do it this way because we need the original square for the other knight
    // when adding the moves to the moveList
    bitboard knights[2];
    int it = 0;
    while(two_knights){
      knights[it] = two_knights & -two_knights;
      it++;
      two_knights &= two_knights - 1;
    }
    //now generate the moves for each knight
    //knight 1
    bitboard knight_moves[] = {6, 10, 15, 17}; //8 total knight moves, >>  and << for each
    if(knights[0]){
      for(int kn_it = 0; kn_it < 4; kn_it++){

        //for the north side
        if(no_ally_piece(ally_board, (knights[0] << knight_moves[kn_it]) & knights[1]) || //check for ally piece in that square
          (knights[0] << knight_moves[kn_it]) != knights[1] || //make sure the other knight isnt in that square
          !(knights[0] & 18374686479671623680ULL) || //bounds check in 8th rank
          ((knight_moves[kn_it] == 15 || knight_moves[kn_it] == 17) && !(knights[0] & 71776119061217280ULL)) || // bounds check in the 7th rank
          ((knight_moves[kn_it] == 15 || knight_moves[kn_it] == 6) && !(knights[0] & 72340172838076673ULL)) || // bounds check in H file
          ((knight_moves[kn_it] == 6) && !(knights[0] & 144680345676153346ULL)) //bounds check in G file
          ){
            moveList.push_back(Board(pos, p, (knights[0] << knight_moves[kn_it]) & knights[1]));
        }

        //for the south side
        if(no_ally_piece(ally_board, (knights[0] >> knight_moves[kn_it]) & knights[1]) || //check for ally piece
          ((knights[0] >> knight_moves[kn_it]) != knights[1]) || //make sure the other knight isnt in that square
          !(knights[0] & 255ULL) || //bounds check rank 1
          ((knight_moves[kn_it] == 15 || knight_moves[kn_it] == 17) && !(knights[0] & 65280ULL)) || //bounds check rank 2
          ((knight_moves[kn_it] == 17 || knight_moves[kn_it] == 10) && !(knights[0] & 9259542123273814144ULL)) || //bounds check in A file
          ((knight_moves[kn_it] == 6 || knight_moves[kn_it] == 10) && !(knights[0] & 4629771061636907072ULL))  //bounds check in B file
          ){
            moveList.push_back(Board(pos, p, (knights[0] >> knight_moves[kn_it]) & knights[1]));
          }

      }
    }
    //knight 2
    if(knights[1]){
      for(int kn_it = 0; kn_it < 4; kn_it++){

        //for the north side
        if(no_ally_piece(ally_board, (knights[1] << knight_moves[kn_it]) & knights[0]) || //check for ally piece in that square
          (knights[1] << knight_moves[kn_it]) != knights[0] || //make sure the other knight isnt in that square
          !(knights[1] & 18374686479671623680ULL) || //bounds check in 8th rank
          ((knight_moves[kn_it] == 15 || knight_moves[kn_it] == 17) && !(knights[1] & 71776119061217280ULL)) || // bounds check in the 7th rank
          ((knight_moves[kn_it] == 15 || knight_moves[kn_it] == 6) && !(knights[1] & 72340172838076673ULL)) || // bounds check in H file
          ((knight_moves[kn_it] == 6) && !(knights[1] & 144680345676153346ULL)) //bounds check in G file
          ){
            moveList.push_back(Board(pos, p, (knights[1] << knight_moves[kn_it]) & knights[0]));
        }

        //for the south side
        if(no_ally_piece(ally_board, (knights[1] >> knight_moves[kn_it]) & knights[0]) || //check for ally piece
          ((knights[1] >> knight_moves[kn_it]) != knights[0]) || //make sure the other knight isnt in that square
          !(knights[1] & 255ULL) || //bounds check rank 1
          ((knight_moves[kn_it] == 15 || knight_moves[kn_it] == 17) && !(knights[1] & 65280ULL)) || //bounds check rank 2
          ((knight_moves[kn_it] == 17 || knight_moves[kn_it] == 10) && !(knights[1] & 9259542123273814144ULL)) || //bounds check in A file
          ((knight_moves[kn_it] == 6 || knight_moves[kn_it] == 10) && !(knights[1] & 4629771061636907072ULL))  //bounds check in B file
          ){
            moveList.push_back(Board(pos, p, (knights[1] >> knight_moves[kn_it]) & knights[0]));
          }
      }
    }
}

bool no_ally_piece (bitboard ally_pieces, bitboard move){
  return (ally_pieces & move) == 0;
}

//TODO do this function, maybe by calling generate moves?
bitboard gen_attacked_squares(Board pos, Side side, bool king){
  return 0;
}
