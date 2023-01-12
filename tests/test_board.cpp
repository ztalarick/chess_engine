// g++ -std=c++17 -o test_board.o test_board.cpp ../src/board.cpp ../src/utils.cpp ../src/move.cpp
/*
  Author: Zachary Talarick
  Date: 05/24/21
  Implements the friend test method declared in board.h
*/
#include <iostream>
#include <string>
#include "../src/board.h" //this is no good, since the filepath can change, should add the directory at compile time

using namespace std;

void PrintStack(stack<Board*> s)
{
    // If stack is empty then return
    if (s.empty())
        return;
     
 
    Board* x = s.top();
 
    // Pop the top element of the stack
    s.pop();
 
    // Recursively call the function PrintStack
    PrintStack(s);
 
    // Print the stack element starting
    // from the bottom
    cout << "____________________ BEGIN _______________________________" << endl;
    x->printBoard();
    cout << "____________________ END _______________________________" << endl;

    // Push the same element onto the stack
    // to preserve the order
    s.push(x);
}



bool cmp_bitboard(bitboard arr1[], bitboard arr2[], int size1, int size2){
  if(size1 != size2){
    return false;
  }

  for(int i = 0; i < size1; i++){
    if(arr1[i] != arr2[i]){
      return false;
    }
  }
  return true;
}

void test(){
  cout << "Running Board class tests: " << endl;
  bool passed = true;

  Board start_pos = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  bitboard start_pos_bitboards[] = {8, 16, 66, 36, 129, 65280, 576460752303423488ULL,
     1152921504606846976ULL, 4755801206503243776ULL, 2594073385365405696ULL, 9295429630892703744ULL, 71776119061217280ULL};
  passed = passed && (start_pos.to_move == 0);
  passed = passed && cmp_bitboard(start_pos.boards, start_pos_bitboards,
    sizeof(start_pos.boards)/sizeof(start_pos.boards[0]), sizeof(start_pos_bitboards)/sizeof(start_pos_bitboards[0]));

  if(passed){
    cout << "\tPassed Start Position" << endl;
  } else {
    cout << "\tFailed Start Position" << endl;
  }

  Board move_1e4 = Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
  passed = passed && (move_1e4.to_move == 1);
  start_pos_bitboards[wpawn] = 134280960ULL;
  passed = passed && cmp_bitboard(move_1e4.boards, start_pos_bitboards,
    sizeof(move_1e4.boards)/sizeof(move_1e4.boards[0]), sizeof(start_pos_bitboards)/sizeof(start_pos_bitboards[0]));

  if(passed){
    cout << "\tPassed 1e4" << endl;
  } else {
    cout << "\tFailed 1e4" << endl;
    // cout << "Expected: " << start_pos_bitboards[wpawn] << " Received: " << move_1e4.boards[wpawn] << endl;
  }

  Board all_pawns = Board("PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP w - - 0 1");
  bitboard all_pawns_bits[] = {0, 0, 0, 0, 0, 18446744073709551615ULL, 0, 0, 0, 0, 0, 0};
  passed = passed && (all_pawns.to_move == 0);
  passed = passed && cmp_bitboard(all_pawns.boards, all_pawns_bits,
    sizeof(all_pawns.boards)/sizeof(all_pawns.boards[0]), sizeof(all_pawns_bits)/sizeof(all_pawns_bits[0]));

  if(passed){
    cout << "\tPassed all_pawns" << endl;
  } else {
    cout << "\tFailed all_pawns" << endl;
    cout << "Expected: " << all_pawns_bits[wpawn] << " Received: " << all_pawns.boards[wpawn] << endl;
    all_pawns.printBoard();
  }

  Board empty = Board("8/8/8/8/8/8/8/8 w - - 0 1");
  bitboard empty_board[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  passed = passed && cmp_bitboard(empty.boards, empty_board,
    sizeof(empty.boards)/sizeof(empty.boards[0]), sizeof(empty_board)/sizeof(empty_board[0]));

  if(passed){
    cout << "\tPassed all_pawns" << endl;
  } else {
    cout << "\tFailed all_pawns" << endl;
  }

}

void test_undo_move(){
  Board start_pos = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

  Move m = Move(134217728ULL, 2048ULL, wpawn); // 1. e4
  Move m2 = Move(34359738368UL, 2251799813685248ULL, bpawn); // 1. e4 e5

  // cout << (start_pos.to_move ? "black" : "white") << endl;
  cout << "____________________ BEGIN _______________________________" << endl;
  start_pos.make_move(m);
  cout << "____________________ END _______________________________" << endl;
  // cout << (start_pos.to_move ? "black" : "white") << endl;
  cout << "____________________ BEGIN _______________________________" << endl;  
  start_pos.make_move(m2);
  cout << "____________________ END _______________________________" << endl;

  cout << (start_pos.to_move ? "black" : "white") << endl;

  // PrintStack(start_pos.game);


  start_pos.undo_move();
  cout << (start_pos.to_move ? "black" : "white") << endl;

}


int main(){
  //test();
  test_undo_move();
}
