/*
  Author: Zachary Talarick
  Date: 05/26/21
  Implements functions to generate all legal moves from a given position
  the moveList is represented as a vector of Boards
  it generates a list of all positions that can be reached by one legal move

  TODO:
    -quiescence list (list of quiet moves)
    -special gen function for when in check
    -Perft testing function
*/

#include "movegen.h"
#include <iostream>
using namespace std;


//for now generate psudeolegal moves
//necessary to make the move and not the entire board state
//TODO generate only legal moves (handle checks/ moving king into check)
int movegen(vector<Move> &moveList, Board pos, bool include_allied_squares){
  if (!pos.to_move){ // 0 - white | 1 - black | so first block is white
    gen_king_moves(moveList, pos, wking, include_allied_squares);
    gen_rook_moves(moveList, pos, wqueen, include_allied_squares);
    gen_bishop_moves(moveList, pos, wqueen, include_allied_squares);
    gen_rook_moves(moveList, pos, wrook, include_allied_squares);
    gen_bishop_moves(moveList, pos, wbishop, include_allied_squares);
    gen_knight_moves(moveList, pos, wknight, include_allied_squares);
    if(!include_allied_squares){
    gen_pawn_moves(moveList, pos, wpawn);
    }
  }else {
    gen_king_moves(moveList, pos, bking, include_allied_squares);
    gen_rook_moves(moveList, pos, bqueen, include_allied_squares);
    gen_bishop_moves(moveList, pos, bqueen, include_allied_squares);
    gen_rook_moves(moveList, pos, brook, include_allied_squares);
    gen_bishop_moves(moveList, pos, bbishop, include_allied_squares);
    gen_knight_moves(moveList, pos, bknight, include_allied_squares);
    if(!include_allied_squares){
    gen_pawn_moves(moveList, pos, bpawn);
    }
  }
  return moveList.size();
}

//function to add the generated king moves to the moveList
//moveList passed by reference
//board passed by reference
//TODO function to check position if king is in check
void gen_king_moves(vector<Move> &moveList, const Board &pos, Piece p, bool include_allied_squares){
      bitboard ally_board = pos.to_move ? pos.black_pieces : pos.white_pieces;
      bitboard curr = 0;

      if((no_ally_piece(ally_board, pos.boards[p] >> 1) || include_allied_squares) &&
      !(pos.boards[p] & 72340172838076673ULL)) //not in h file
        moveList.push_back(Move(pos.boards[p] >> 1, pos.boards[p], p)); //move 1 east

      if((no_ally_piece(ally_board, pos.boards[p] << 1) || include_allied_squares) && 
        !(pos.boards[p] & 9259542123273814144ULL)) //check that the king is not on the A file
        moveList.push_back(Move(pos.boards[p] << 1, pos.boards[p], p)); //move 1 west

      if((no_ally_piece(ally_board, pos.boards[p] >> 8) || include_allied_squares) &&
       !(pos.boards[p] & 255ULL)) //not on 1st rank
        moveList.push_back(Move(pos.boards[p] >> 8, pos.boards[p], p)); //move 1 south

      if((no_ally_piece(ally_board, pos.boards[p] << 8) || include_allied_squares) &&
       !(pos.boards[p] & 18374686479671623680ULL)) //not on 8th rank
        moveList.push_back(Move(pos.boards[p] << 8, pos.boards[p], p)); //move 1 north

      if((no_ally_piece(ally_board, pos.boards[p] << 7) || include_allied_squares) &&
       !(pos.boards[p] & 18374969058471772417ULL)) //not in h file for 8th rank
        moveList.push_back(Move(pos.boards[p] << 7, pos.boards[p], p)); //move 1 ne

      if((no_ally_piece(ally_board, pos.boards[p] << 9) || include_allied_squares) &&
      !(pos.boards[p] & 18410856566090662016ULL)) //not in a file or 8th rank
        moveList.push_back(Move(pos.boards[p] << 9, pos.boards[p], p)); //move 1 nw

      if((no_ally_piece(ally_board, pos.boards[p] >> 7) || include_allied_squares) &&
      !(pos.boards[p] & 9259542123273814271ULL)) //not in a file or 1st rank
        moveList.push_back(Move(pos.boards[p] >> 7, pos.boards[p], p)); //move 1 sw

      if((no_ally_piece(ally_board, pos.boards[p] >> 9) || include_allied_squares) &&
      !(pos.boards[p] & 72340172838076927ULL)) //not in h file or 1st rank
        moveList.push_back(Move(pos.boards[p] >> 9, pos.boards[p], p)); //move 1 se
      
      //TODO: add castle
}

//function to generate and add all legal knight moves to the moveList
//moveList and board passed by reference
void gen_knight_moves(vector<Move> &moveList, const Board &pos, Piece p, bool include_allied_squares){
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
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 13889313184910721279ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) << 6;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 18375534216072069891ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) >> 10;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 217020518514230271ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) << 10;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 18428941609300181184ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) >> 15;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 9259542123273846783ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) << 15;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 18446463702556279041ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) >> 17;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 72340172838141951ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));

        curr_move = sep_knights.at(curr_kn) << 17;
        if((no_ally_piece(ally_board, curr_move) || include_allied_squares) && !(sep_knights.at(curr_kn) & 18446603888132915328ULL))
          moveList.push_back(Move(curr_move, sep_knights.at(curr_kn), p));
      } else{
        break; //if you reach an index with no knight you can stop the loop
      }
    }
}

/* generate all legal pawn moves and add to the moveList
possible moves:
White:
   << 8  - no pieces in front and no promotion
   << 8  - no pieces in front and promotion
   << 16 - only on 2nd rank
   << 9  - attacking and not in a file and no promotion
   << 9  - attacking and not in a file and promotion
   << 7  - attacking and not in h file and no promotion
   << 7  - attacking and not in h file and promotion
Black:
   >> 8  - no pieces in front and no promotion
   >> 8  - no pieces in front and promotion
   >> 16 - only on 2nd rank
   >> 9  - attacking and not in a file and no promotion
   >> 9  - attacking and not in a file and promotion
   >> 7  - attacking and not in h file and no promotion
   >> 7  - attacking and not in h file and promotion */
void gen_pawn_moves(vector<Move> &moveList, const Board &pos, Piece p){
      bitboard ally_board = pos.to_move ? pos.black_pieces : pos.white_pieces;
      bitboard opp_board = pos.to_move ? pos.white_pieces : pos.black_pieces;
      bitboard all_pawns = pos.boards[p]; //every pawn
      vector<bitboard> sep_pawns(8);
      separate_bits(sep_pawns, all_pawns); //seperate pawns
      bitboard curr_move;

      if(p == wpawn){ // white moves
        for(int i = 0; i < 8; i++){ //iterate through seperated pawns
          if(!sep_pawns.at(i))
            break;
          curr_move = sep_pawns.at(i) << 8; //single foward push
          //if there is no piece allied or oponent
          if(no_ally_piece(ally_board, curr_move) && no_ally_piece(opp_board, curr_move)){
            
            if(curr_move & 18374686479671623680ULL){ //promotion
              moveList.push_back(Move(0, sep_pawns.at(i), p, wqueen));
              moveList.push_back(Move(0, sep_pawns.at(i), p, wrook));
              moveList.push_back(Move(0, sep_pawns.at(i), p, wknight));
              moveList.push_back(Move(0, sep_pawns.at(i), p, wbishop));
            }else { //no promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p));
            }
          }
            
          curr_move = sep_pawns.at(i) << 16; //double move
          if((sep_pawns.at(i) & 65280ULL) && no_ally_piece(ally_board, curr_move) //check on 2nd rank
          && no_ally_piece(opp_board, curr_move)){
            moveList.push_back(Move(curr_move, sep_pawns.at(i), p, curr_move >> 8));
          }

          curr_move = sep_pawns.at(i) << 9; //left capture
          if(
            !(sep_pawns.at(i) & 9259542123273814144ULL) //not on the A file
          &&
            no_ally_piece(ally_board, curr_move) //there is no allied piece on the targeted square 
          && 
          (!(no_ally_piece(opp_board, curr_move)) //there is an opponent piece on the targeted square
          || 
          !(no_ally_piece(pos.en_passant, curr_move)))){ //there is an en passant available 

            if(curr_move & 18374686479671623680ULL){ //promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p, wqueen));
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p, wrook));
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p, wknight));
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p, wbishop));
            }else { //no promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p));

            }
          } 
          //no piece allied or oponent, and it does not move to promotion square        
          curr_move = sep_pawns.at(i) << 7; //right capture
          if(
            !(sep_pawns.at(i) & 72340172838076673ULL)//not on the H file
          &&
            (no_ally_piece(ally_board, curr_move)  
          && ((!(no_ally_piece(opp_board, curr_move))))
          || !(no_ally_piece(pos.en_passant, curr_move))) 
           ){ 

            if(curr_move & 18374686479671623680ULL){ //promotion
              moveList.push_back(Move(0, sep_pawns.at(i), p, wqueen));
              moveList.push_back(Move(0, sep_pawns.at(i), p, wrook));
              moveList.push_back(Move(0, sep_pawns.at(i), p, wknight));
              moveList.push_back(Move(0, sep_pawns.at(i), p, wbishop));
            }else { //no promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p));
            }
          } 
        }
      }else { // black moves
        for(int i = 0; i < 8; i++){ //iterate through seperated pawns
          if(!sep_pawns.at(i))
            break;
          curr_move = sep_pawns.at(i) >> 8; //single foward push
          //if there is no piece allied or oponent
          if(no_ally_piece(ally_board, curr_move) && no_ally_piece(opp_board, curr_move)){
            
            if(curr_move & 255ULL){ //promotion
              moveList.push_back(Move(0, sep_pawns.at(i), p, bqueen));
              moveList.push_back(Move(0, sep_pawns.at(i), p, brook));
              moveList.push_back(Move(0, sep_pawns.at(i), p, bknight));
              moveList.push_back(Move(0, sep_pawns.at(i), p, bbishop));
            }else { //no promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p));
            }
          }
            
          curr_move = sep_pawns.at(i) >> 16; //double move
          if((sep_pawns.at(i) & 71776119061217280ULL) && no_ally_piece(ally_board, curr_move) //check on 2nd rank
          && no_ally_piece(opp_board, curr_move)){
            moveList.push_back(Move(curr_move, sep_pawns.at(i), p, curr_move << 8));
          }

          curr_move = sep_pawns.at(i) >> 9; //left capture
          if(
            !(sep_pawns.at(i) & 72340172838076673ULL)//not on the H file
          &&
            no_ally_piece(ally_board, curr_move) //there is no allied piece on the targeted square 
          && (!(no_ally_piece(opp_board, curr_move))//there is an opponent piece on the targeted square
          || !(no_ally_piece(pos.en_passant, curr_move)))){ //there is an en passant available 

            if(curr_move & 255ULL){ //promotion
              moveList.push_back(Move(0, sep_pawns.at(i), p, bqueen));
              moveList.push_back(Move(0, sep_pawns.at(i), p, brook));
              moveList.push_back(Move(0, sep_pawns.at(i), p, bknight));
              moveList.push_back(Move(0, sep_pawns.at(i), p, bbishop));
            }else { //no promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p));
            }
          } 
          //no piece allied or oponent, and it does not move to promotion square        
          curr_move = sep_pawns.at(i) >> 7; //right capture
          if(!(sep_pawns.at(i) & 9259542123273814144ULL) //not on the A file
          &&
          no_ally_piece(ally_board, curr_move)  
          && (!(no_ally_piece(opp_board, curr_move))
          || !(no_ally_piece(pos.en_passant, curr_move)))){

            if(curr_move & 255ULL){ //promotion
              moveList.push_back(Move(0, sep_pawns.at(i), p, bqueen));
              moveList.push_back(Move(0, sep_pawns.at(i), p, brook));
              moveList.push_back(Move(0, sep_pawns.at(i), p, bknight));
              moveList.push_back(Move(0, sep_pawns.at(i), p, bbishop));
            }else { //no promotion
              moveList.push_back(Move(curr_move, sep_pawns.at(i), p));
            }
          }       
      }
    }
}

//generate all legal rook moves and add to the moveList
//rooks are sliding pieces and should be shifted in a loop in four different directions
// >> 8
// << 8
// >> 1
// << 1
void gen_rook_moves(vector<Move> &moveList, const Board &pos, Piece p, bool include_allied_squares){
  bitboard ally_board = pos.to_move ? pos.black_pieces : pos.white_pieces;
  bitboard opp_board = pos.to_move ? pos.white_pieces : pos.black_pieces;
  bitboard curr_move;
  bitboard all_rooks = pos.boards[p];

  vector<bitboard> sep_rooks(10);
  separate_bits(sep_rooks, all_rooks);

  for(int curr_rk = 0; curr_rk < 10; curr_rk++){
    if(!sep_rooks.at(curr_rk)){ //if there is no rook at the current index
      break;
    }

    // << 8
    bitboard old = sep_rooks[curr_rk];
    //if(!(old &) && !(old &))
    if(!(old & 18374686479671623680ULL)){ // begin on the 8th rank
      curr_move = sep_rooks[curr_rk] << 8;
      if(curr_move != 0){
        for(int up = 0; up < 8; up++){
          if(up != 0){
            curr_move = curr_move << 8;
          }
          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move) //there is an opponent piece on the current move (we are capturing)
          || (curr_move & 18374686479671623680ULL)){ //on the 8th rank
            break; //stop sliding
          }
        }
      }
    }
    // >> 8
    if(!(old & 255ULL)){  //begin on the first rank
      curr_move = sep_rooks[curr_rk] >> 8;
      if(curr_move != 0){
        for(int down = 0; down < 8; down++){
          if(down != 0){
          curr_move = curr_move >> 8;
          }

          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece 
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move)  //there is an opponent piece
          || (curr_move & 255ULL)){                 //on the first rank
            break; //stop sliding
          }
        }
      }
    }

    // >> 1
    if(!(old & 72340172838076673ULL)){
      curr_move = sep_rooks[curr_rk] >> 1;
      if(curr_move != 0){
        for(int right = 0; right < 8; right++){
          if(right != 0){
          curr_move = curr_move >> 1;
          }
          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move)
          || (curr_move & 72340172838076673ULL)){ //there is an opponent piece
            break; //stop sliding
          }
        }
      }
    }

    if(!(old & 9259542123273814144ULL)){
      curr_move = sep_rooks[curr_rk] << 1;
      if(curr_move != 0){
        for(int left = 0; left < 8; left++){
          if(left != 0){
          curr_move = curr_move << 1;
          }
          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move)
          || (curr_move & 9259542123273814144ULL)){ //there is an opponent piece
            break; //stop sliding after capture
          }
        }
      }
    }
  }
}

//generate all legal bishop moves and add to moveList
//very similar to gen_rook_moves just diagonal
// >> 9 - SE
// << 9 - NW
// >> 7 - SW
// << 7 - NE
void gen_bishop_moves(vector<Move> &moveList, const Board &pos, Piece p, bool include_allied_squares){
  bitboard ally_board = pos.to_move ? pos.black_pieces : pos.white_pieces;
  bitboard opp_board = pos.to_move ? pos.white_pieces : pos.black_pieces;
  bitboard curr_move;
  bitboard all_bishops = pos.boards[p];

  vector<bitboard> sep_bishops(10);
  separate_bits(sep_bishops, all_bishops);

  for(int curr_bshp = 0; curr_bshp < 10; curr_bshp++){
    if(!sep_bishops.at(curr_bshp)){ //if there is no bishop at the current index
      break;
    }

    // << 9 - NW
    bitboard old = sep_bishops[curr_bshp];
    if(!(old & 18374686479671623680ULL) && !(old & 9259542123273814144ULL)){ //begins on //on the 8th rank or A file
      curr_move = sep_bishops[curr_bshp] << 9;
      if(curr_move != 0){
        for(int nw = 0; nw < 8; nw++){
          if(nw != 0){
            curr_move = curr_move << 9;
          }
          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));
          if(!no_ally_piece(opp_board, curr_move) //there is an opponent piece
          || (curr_move & 18374686479671623680ULL) || (curr_move & 9259542123273814144ULL)){ //on the 8th rank or A file
            break; //stop sliding
          }
        }
      }
    }
    // >> 9 - SE

    if(!(old & 255ULL) && !(old & 72340172838076673ULL)){ //begins on the first rank or in H file
      curr_move = sep_bishops[curr_bshp] >> 9;
      if(curr_move != 0){
        for(int se = 0; se < 8; se++){
          if(se != 0){
          curr_move = curr_move >> 9;
          }

          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece 
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move)  //there is an opponent piece
          || (curr_move & 255ULL) || (curr_move & 72340172838076673ULL)){ //on the first rank or in H file
            break; //stop sliding
          }
        }
      }
    }

    // >> 7 - SW
    if(!(old & 9259542123273814144ULL) && !(old & 255ULL)){  // begins on the first rank or in A file
      curr_move = sep_bishops[curr_bshp] >> 7;
      if(curr_move != 0){
        for(int sw = 0; sw < 8; sw++){
          if(sw != 0){
          curr_move = curr_move >> 7;
          }
          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move) //there is an opponent piece
          || (curr_move & 9259542123273814144ULL) || (curr_move & 255ULL)){  //on the first rank or in A file
            break; //stop sliding
          }
        }
      }
    }
    // << 7 - NE
    if(!(old & 18374969058471772417ULL)){ // on the eigth rank or h file
      curr_move = sep_bishops[curr_bshp] << 7;
      if(curr_move != 0){
        for(int ne = 0; ne < 8; ne++){
          if(ne != 0){
          curr_move = curr_move << 7;
          }
          if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
            if(include_allied_squares){
              moveList.push_back(Move(curr_move, old, p));
            }
            break; //stop sliding in this direction
          }
          //add the capture to the moveList
          moveList.push_back(Move(curr_move, old, p));

          if(!no_ally_piece(opp_board, curr_move) //there is an opponent piece
          || (curr_move & 18374969058471772417ULL)){ // on the eigth rank or h file
            break; //stop sliding after capture
          }
        }
      }
    }
  }
}

bool no_ally_piece (bitboard ally_pieces, bitboard move){
  return (ally_pieces & move) == 0;
}

//This function seperates each bit into a seperate 
void separate_bits(vector<bitboard> &bits, bitboard board){
  int it = 0;
  while (board){
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

void print_moveList2(vector<Move> &moveList){
    int num_moves = 0;
    cout << endl << "Move List: " << endl;
    for(Move m: moveList){
        cout << endl << "__________________ BEGIN __________________" << endl;
        m.print_move();
        cout << endl << "__________________ END __________________" << endl;
        num_moves++;
    }
    cout << "Number of moves generated: " << num_moves << endl << endl; 
}


bitboard gen_attacked_squares(Board pos){
  //get opposite side 
  Side s = pos.to_move ? black : white;
  bitboard attacked_squares = 0;
  vector<Move> moveList;

  //remove the oposing king from the movegen to catch the case of moving away from sliding checks
  Piece k = s ? wking : bking;
  bitboard prev_king = pos.boards[k];
  pos.boards[k] = 0;
  pos.to_move = s;

  //we cannot just call movegen because we only want attacking pawn moves
  //handle pawns
  Piece pawns = s ? bpawn : wpawn;
  vector<bitboard> all_pawns(8);
  separate_bits(all_pawns, pos.boards[pawns]);
  for(int curr_pawn = 0; curr_pawn < 8; curr_pawn++){
    if(!all_pawns.at(curr_pawn)){ //if there is no pawn at the current index
      break;
    }
    if(pawns == wpawn){
      if(!(all_pawns.at(curr_pawn) & 72340172838076673ULL)){ //not h file
        attacked_squares = attacked_squares | (all_pawns.at(curr_pawn) << 7);
      }
      if(!(all_pawns.at(curr_pawn) & 9259542123273814144ULL)){ //not a file
        attacked_squares = attacked_squares | (all_pawns.at(curr_pawn) << 9);
      }
    }else if (pawns == bpawn){
      if(!(all_pawns.at(curr_pawn) & 72340172838076673ULL)){ //not h file
        attacked_squares = attacked_squares | (all_pawns.at(curr_pawn) >> 9);
      }
      if(!(all_pawns.at(curr_pawn) & 9259542123273814144ULL)){ //not a file
        attacked_squares = attacked_squares | (all_pawns.at(curr_pawn) >> 7);
      }
    }
  }
  //build moveList from individual piece functions
  //we must also include the square attacking allied pieces are on
  movegen(moveList, pos, true);
  //iterate through moveList and combine attacked squares
  for(Move m : moveList){
    attacked_squares = attacked_squares | m.move;

  }
  return attacked_squares;
}

void gen_promotion(vector<Move> &moveList, Board &pos, Move m, bitboard prev_king){
  if(m.promote == none || m.move == prev_king){
    return;
  }
  pos.promote(m.p, m.promote, m.move);
  //would be way cooler to make this a map but the syntax in c++ is awful
  if(m.promote == wqueen || m.promote == bqueen){
    gen_rook_moves(moveList, pos, m.promote, false);
    gen_bishop_moves(moveList, pos, m.promote, false);
  }

  if(m.promote == wbishop || m.promote == bbishop){
    gen_bishop_moves(moveList, pos, m.promote, false);
  }

  if(m.promote == wrook || m.promote == brook){
    gen_rook_moves(moveList, pos, m.promote, false);
  }

  if(m.promote == wknight || m.promote == bknight){
    gen_knight_moves(moveList, pos, m.promote, false);
  }
}
