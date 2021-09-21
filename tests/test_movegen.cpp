/*
  Author: Zachary Talarick
  Date: 05/24/21
  Tests for the movegen.cpp file
*/

// g++ -o test_movegen.exe test_movegen.cpp ../src/board.cpp ../src/movegen.cpp


#include <iostream>
#include <vector>

#include "../src/board.h"
#include "../src/movegen.h"


using namespace std;


void print_moveList(vector<Board> &moveList){
    int num_moves = 0;
    for(Board b: moveList){
        b.printBoard();
        cout << endl;
        num_moves++;
    }
    cout << "Number of moves generated: " << num_moves << endl << endl; 
}

void test_gen_king_moves(){
    vector<Board> moveList;
 
    cout << "Test for gen_king_moves: " << endl;

    // only a king on d4
    Board solo_king = Board("8/8/8/8/3K4/8/8/8 w - - 0 1");
    cout << "Test 1 - King on d4: " << endl << endl;
    gen_king_moves(moveList, solo_king, wking);
    print_moveList(moveList);

    moveList.clear();

    // king on d4 surrounded by pawns
    Board ally_pieces = Board("8/8/8/2PPP3/2PKP3/2PPP3/8/8 w - - 0 1");
    cout << endl << "Test 2 - King on d4 surrounded by allied pawns: " << endl << endl;
    gen_king_moves(moveList, ally_pieces, wking);
    print_moveList(moveList);

    moveList.clear();

    // king on A1
    Board king_a1 = Board("8/8/8/8/8/8/8/K7 w - - 0 1");
    cout << endl << "Test 3 - King on a1: " << endl << endl;
    gen_king_moves(moveList, king_a1, wking);
    print_moveList(moveList);

    moveList.clear();

    //King on A8 
    Board king_a8 = Board("K7/8/8/8/8/8/8/8 w - - 0 1");
    cout << endl << "Test 4 - King on a8: " << endl << endl;
    gen_king_moves(moveList, king_a8, wking);
    print_moveList(moveList);

    moveList.clear();

    //King on h8
    Board king_h8 = Board("7K/8/8/8/8/8/8/8 w - - 0 1");
    cout << endl << "Test 5 - King on h8: " << endl << endl;
    gen_king_moves(moveList, king_h8, wking);
    print_moveList(moveList);

    moveList.clear();

    //King on h1
    Board king_h1 = Board("8/8/8/8/8/8/8/7K w - - 0 1");
    cout << endl << "Test 6 - King on h1: " << endl << endl;
    gen_king_moves(moveList, king_h1, wking);
    print_moveList(moveList);

    moveList.clear();

    //Black king on d4
    Board bking_d4 = Board("8/8/8/8/3k4/8/8/8 b - - 0 1");
    cout << endl << "Test 7 - Black King on d4: " << endl << endl;
    gen_king_moves(moveList, bking_d4, bking);
    print_moveList(moveList);

    moveList.clear();


}

void test_gen_knight_moves(){
    vector<Board> moveList;
    cout << "Tests for gen_knight_moves" << endl;

    //knight on d4
    cout << "Test 1 - Knight on d4: " << endl;
    Board knight_d4 = Board("8/8/8/8/3N4/8/8/8 w - - 0 1");
    gen_knight_moves(moveList, knight_d4, wknight);   
    print_moveList(moveList);

    moveList.clear();

    //knight on d4 and e4
    cout << "Test 2 - Knight on d4 and e4: " << endl;
    Board knight_d4_e4 = Board("8/8/8/8/3NN3/8/8/8 w - - 0 1");
    gen_knight_moves(moveList, knight_d4_e4, wknight);
    print_moveList(moveList);

    moveList.clear();

    //knight on d4, allied pawns on all target squares
    cout << "Test 3 - Knight on d4, allied pawns on all target squares: " << endl;
    Board knight_d4_allied_pawns = Board("8/8/2P1P3/1P3P2/3N4/1P3P2/2P1P3/8 w - - 0 1");
    gen_knight_moves(moveList, knight_d4_allied_pawns, wknight);
    print_moveList(moveList);

    moveList.clear();

    //knights in all 4 corners
    cout << "Test 4 - Knight on all 4 corners: " << endl;
    Board knight_4corners = Board("N6N/8/8/8/8/8/8/N6N w - - 0 1");
    gen_knight_moves(moveList, knight_4corners, wknight);
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 5 - Knight on d4, blocked by allied pawns except for capture" << endl;
    Board knight_d4_capture = Board("8/8/2P1P3/1P3p2/3N4/1P3P2/2P1P3/8 w - - 0 1");
    gen_knight_moves(moveList, knight_d4_capture, wknight);
    print_moveList(moveList);

    moveList.clear();
}

void test_gen_pawn_moves(){
    vector<Board> moveList;
    cout << "Tests for gen_pawn_moves" << endl;

    //pawn on e2 and d4
    cout << "Test 1 - Pawn on e2 and d4: " << endl;
    Board pawn_e2_d4 = Board("8/8/8/8/3P4/8/4P3/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_e2_d4, wpawn);   
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 2 - Pawn on d7" << endl;
    Board pawn_d7 = Board("8/3P4/8/8/8/8/8/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_d7, wpawn); 
    print_moveList(moveList);  

    moveList.clear();

    cout << "Test 3 - Pawn on blocked on d4" << endl;
    Board pawn_blocked_d4 = Board("8/8/8/3k4/3P4/8/8/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_blocked_d4, wpawn); 
    print_moveList(moveList);  

    moveList.clear();

    cout << "Test 4 - Pawn on d4 with captures" << endl;
    Board pawn_captures_d4 = Board("8/8/8/2rrr3/3P4/8/8/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_captures_d4, wpawn); 
    print_moveList(moveList); 

    moveList.clear();

    cout << "Test 5 - Multiple pawns with promotion" << endl;
    Board pawn_promotion = Board("8/3P4/8/8/8/4PPP1/8/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_promotion, wpawn); 
    print_moveList(moveList); 

    moveList.clear();

    cout << "Test 6 - Pawns with capture promotion" << endl;
    Board pawn_capture_promotion = Board("2rrr3/3P4/8/8/8/8/8/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_capture_promotion, wpawn); 
    print_moveList(moveList); 

    moveList.clear();

}

int main(){
    //test_gen_king_moves();
    //test_gen_knight_moves();
    test_gen_pawn_moves();

}