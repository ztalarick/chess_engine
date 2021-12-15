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
//TODO generate only legal moves (handle checks/ moving king into check)
vector<Board> movegen(vector<Board> &moveList, Board pos){
  //iterate every piece type that can move
  //use the fancy inline if statement to evaluate i to the correct indices
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
      gen_rook_moves(moveList, pos, p);
    }
    if(p == wpawn || p == bpawn){
      gen_pawn_moves(moveList, pos, p);
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

//generate all legal pawn moves and add to the moveList
//possible moves:
// White:
//    << 8  - no pieces in front and no promotion
//    << 8  - no pieces in front and promotion
//    << 16 - only on 2nd rank
//    << 9  - attacking and not in a file and no promotion
//    << 9  - attacking and not in a file and promotion
//    << 7  - attacking and not in h file and no promotion
//    << 7  - attacking and not in h file and promotion
// Black:
//    >> 8  - no pieces in front and no promotion
//    >> 8  - no pieces in front and promotion
//    >> 16 - only on 2nd rank
//    >> 9  - attacking and not in a file and no promotion
//    >> 9  - attacking and not in a file and promotion
//    >> 7  - attacking and not in h file and no promotion
//    >> 7  - attacking and not in h file and promotion
void gen_pawn_moves(vector<Board> &moveList, const Board &pos, Piece p){
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
            bitboard new_pawns = combine_bits(sep_pawns, curr_move, sep_pawns.at(i));
            
            if(curr_move & 18374686479671623680ULL){ //promotion
              Board new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wqueen, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wrook, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wknight, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wbishop, curr_move);
              moveList.push_back(new_board);
            }else { //no promotion
              moveList.push_back(Board(pos, p, new_pawns));
            }
          }
            
          curr_move = sep_pawns.at(i) << 16; //double move
          if((sep_pawns.at(i) & 65280ULL) && no_ally_piece(ally_board, curr_move) //check on 2nd rank
          && no_ally_piece(opp_board, curr_move)){
            Board new_board = Board(pos, p, combine_bits(sep_pawns, curr_move, sep_pawns.at(i)));
            new_board.set_en_passant(curr_move >> 8); //set enpassant
            moveList.push_back(new_board);
          }

          
          curr_move = sep_pawns.at(i) << 9; //left capture
          if(
            (no_ally_piece(ally_board, curr_move) //there is no allied piece on the targeted square 
          && 
          (!(no_ally_piece(opp_board, curr_move)))) //there is an opponent piece on the targeted square
          || 
          (!(no_ally_piece(pos.en_passant, curr_move)) //there is an en passant available
          && 
          !(sep_pawns.at(i) & 9259542123273814144ULL))){ //not on the A file
            bitboard new_pawns = combine_bits(sep_pawns, curr_move, sep_pawns.at(i));

            if(curr_move & 18374686479671623680ULL){ //promotion
              Board new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wqueen, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wrook, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wknight, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wbishop, curr_move);
              moveList.push_back(new_board);
            }else { //no promotion
              moveList.push_back(Board(pos, p, new_pawns));

            }
          } 
          //no piece allied or oponent, and it does not move to promotion square        
          curr_move = sep_pawns.at(i) << 7; //right capture
          if((no_ally_piece(ally_board, curr_move)  
          && (!(no_ally_piece(opp_board, curr_move))))
          || ((!(no_ally_piece(pos.en_passant, curr_move))) 
          && !(sep_pawns.at(i) & 72340172838076673ULL))){ //not on the H file
            bitboard new_pawns = combine_bits(sep_pawns, curr_move, sep_pawns.at(i));

            if(curr_move & 18374686479671623680ULL){ //promotion
              Board new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wqueen, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wrook, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wknight, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, wbishop, curr_move);
              moveList.push_back(new_board);
            }else { //no promotion
              moveList.push_back(Board(pos, p, new_pawns));

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
            bitboard new_pawns = combine_bits(sep_pawns, curr_move, sep_pawns.at(i));
            
            if(curr_move & 255ULL){ //promotion
              Board new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bqueen, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, brook, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bknight, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bbishop, curr_move);
              moveList.push_back(new_board);
            }else { //no promotion
              moveList.push_back(Board(pos, p, new_pawns));
            }
          }
            
          curr_move = sep_pawns.at(i) >> 16; //double move
          if((sep_pawns.at(i) & 71776119061217280ULL) && no_ally_piece(ally_board, curr_move) //check on 2nd rank
          && no_ally_piece(opp_board, curr_move)){
            Board new_board = Board(pos, p, combine_bits(sep_pawns, curr_move, sep_pawns.at(i)));
            new_board.set_en_passant(curr_move << 8); //set enpassant
            moveList.push_back(new_board);
          }

          
          curr_move = sep_pawns.at(i) >> 9; //left capture
          if((no_ally_piece(ally_board, curr_move) //there is no allied piece on the targeted square 
          && (!(no_ally_piece(opp_board, curr_move))))//there is an opponent piece on the targeted square
          || (!(no_ally_piece(pos.en_passant, curr_move)) //there is an en passant available
          && !(sep_pawns.at(i) & 72340172838076673ULL))){ //not on the H file
            bitboard new_pawns = combine_bits(sep_pawns, curr_move, sep_pawns.at(i));

            if(curr_move & 255ULL){ //promotion
              Board new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bqueen, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, brook, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bknight, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bbishop, curr_move);
              moveList.push_back(new_board);
            }else { //no promotion
              moveList.push_back(Board(pos, p, new_pawns));

            }
          } 
          
          
          //no piece allied or oponent, and it does not move to promotion square        
          curr_move = sep_pawns.at(i) >> 7; //right capture
          if((no_ally_piece(ally_board, curr_move)  
          && (!(no_ally_piece(opp_board, curr_move))))
          || ((!(no_ally_piece(pos.en_passant, curr_move))) 
          && !(sep_pawns.at(i) & 9259542123273814144ULL))){ //not on the A file
            bitboard new_pawns = combine_bits(sep_pawns, curr_move, sep_pawns.at(i));

            if(curr_move & 255ULL){ //promotion
              Board new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bqueen, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, brook, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bknight, curr_move);
              moveList.push_back(new_board);

              new_board = Board(pos, p, new_pawns);
              new_board.promote(p, bbishop, curr_move);
              moveList.push_back(new_board);
            }else { //no promotion
              moveList.push_back(Board(pos, p, new_pawns));

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
void gen_rook_moves(vector<Board> &moveList, const Board &pos, Piece p){
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
    curr_move = sep_rooks[curr_rk] << 8;
    if(curr_move != 0){
      for(int up = 0; up < 8; up++){
        if(up != 0){
          curr_move = curr_move << 8;
        }
        if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece
          break; //stop sliding in this direction
        }
        //add the capture to the moveList
        moveList.push_back(Board(pos, p, combine_bits(sep_rooks, curr_move, sep_rooks.at(curr_rk))));

        if(!no_ally_piece(opp_board, curr_move) //there is an opponent piece
        || (curr_move & 18374686479671623680ULL)){ //on the 8th rank
          break; //stop sliding
        }
      }
    }

    // >> 8
    curr_move = sep_rooks[curr_rk] >> 8;
    if(curr_move != 0){
      for(int down = 0; down < 8; down++){
        if(down != 0){
        curr_move = curr_move >> 8;
        }

        if(!no_ally_piece(ally_board, curr_move)){ //there is an allied piece 
          break; //stop sliding in this direction
        }
        //add the capture to the moveList
        moveList.push_back(Board(pos, p, combine_bits(sep_rooks, curr_move, sep_rooks.at(curr_rk))));

        if(!no_ally_piece(opp_board, curr_move)  //there is an opponent piece
        || (curr_move & 255ULL)){                 //on the first rank
          break; //stop sliding
        }
      }
    }


    // >> 1
    curr_move = sep_rooks[curr_rk] >> 1;
    if(curr_move != 0){
      for(int right = 0; right < 8; right++){
        if(right != 0){
        curr_move = curr_move >> 1;
        }
        if(!no_ally_piece(ally_board, curr_move) //there is an allied piece
        ){  //on the H file
          break; //stop sliding in this direction
        }
        //add the capture to the moveList
        moveList.push_back(Board(pos, p, combine_bits(sep_rooks, curr_move, sep_rooks.at(curr_rk))));

        if(!no_ally_piece(opp_board, curr_move)
        || (curr_move & 72340172838076673ULL)){ //there is an opponent piece
          break; //stop sliding
        }
      }
    }
    

    curr_move = sep_rooks[curr_rk] << 1;
    if(curr_move != 0){
      for(int left = 0; left < 8; left++){
        if(left != 0){
        curr_move = curr_move << 1;
        }
        if(!no_ally_piece(ally_board, curr_move) //there is an allied piece
        ){ //on the A file
          break; //stop sliding in this direction
        }
        //add the capture to the moveList
        moveList.push_back(Board(pos, p, combine_bits(sep_rooks, curr_move, sep_rooks.at(curr_rk))));

        if(!no_ally_piece(opp_board, curr_move)
        || (curr_move & 9259542123273814144ULL)){ //there is an opponent piece
          break; //stop sliding after capture
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

//TODO do this function, maybe by calling generate moves?
bitboard gen_attacked_squares(Board pos, Side side, bool king){
  return 0;
}
