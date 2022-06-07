/*
  Author: Zachary Talarick
  Date: 05/24/21
  Tests for the movegen.cpp file
*/

// g++ -std=c++17 -o test_movegen.exe test_movegen.cpp ../src/board.cpp ../src/movegen.cpp
// g++ -std=c++17 -o test_movegen.o test_movegen.cpp ../src/board.cpp ../src/movegen.cpp



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

    cout << "Test 7 - Pawn on d4 capturing other pawns" << endl;
    Board pawn_captures_d4_pawn = Board("8/8/8/2ppp3/3P4/8/8/8 w - - 0 1");
    gen_pawn_moves(moveList, pawn_captures_d4_pawn, wpawn); 
    print_moveList(moveList); 

    moveList.clear();

    cout << "Test 8 - En Passant left" << endl;
    Board en_passant_left = Board("8/8/8/3pP3/8/8/8/8 w - d6 0 1");
    gen_pawn_moves(moveList, en_passant_left, wpawn);
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 9 - En Passant right" << endl;
    Board en_passant_right = Board("8/8/8/4Pp2/8/8/8/8 w - f6 0 1");
    gen_pawn_moves(moveList, en_passant_right, wpawn);
    print_moveList(moveList);

}

void test_gen_rook_moves(){
    vector<Board> moveList;

    cout << "Test for gen_rook_moves: " << endl;

    cout << "Test 1 rook on d4" << endl;
    Board rook_d4 = Board("8/8/8/8/3R4/8/8/8 w - - 0 1");
    gen_rook_moves(moveList, rook_d4, wrook);   
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 2 black rook on d4" << endl;
    Board black_rook_d4 = Board("8/8/8/8/3r4/8/8/8 b - - 0 1");
    gen_rook_moves(moveList, black_rook_d4, brook);   
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 3: rook on d1" << endl;
    Board rook_d1 = Board("8/8/8/8/8/8/8/3R4 w - - 0 1");
    gen_rook_moves(moveList, rook_d1, wrook);
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 4: rook on d4 and allied pawn on d5" << endl;
    Board rook_d4_pawn = Board("8/8/8/3P4/3R4/8/8/8 w - - 0 1");
    gen_rook_moves(moveList, rook_d4_pawn, wrook);
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 5: white rook on d4 and black pawn on d5" << endl;
    Board rook_d4_black_pawn = Board("8/8/8/3p4/3R4/8/8/8 w - - 0 1");
    gen_rook_moves(moveList, rook_d4_black_pawn, wrook);
    print_moveList(moveList);

    moveList.clear();

    cout << "Test 6: multiple rooks" << endl;
    Board rook_d4_e5 = Board("8/8/8/4R3/3R4/8/8/8 w - - 0 1");
    gen_rook_moves(moveList, rook_d4_e5, wrook);
    print_moveList(moveList);

    moveList.clear();
}

void test_gen_bishop_moves(){
    vector<Board> moveList;

    cout << "Test for gen_bishop_moves: " << endl;

    cout << "Test 1 bishop on d4" << endl;
    Board bishop_d4 = Board("8/8/8/8/3B4/8/8/8 w - - 0 1");
    gen_bishop_moves(moveList, bishop_d4, wbishop);   
    print_moveList(moveList);

    moveList.clear();
}

void test_gen_queen_moves(){
    vector<Board> moveList;

    cout << "Test for gen_queen_moves: " << endl;

    cout << "Test 1 queen on d4" << endl;
    Board queen_d4 = Board("8/8/8/8/3Q4/8/8/8 w - - 0 1");
    gen_rook_moves(moveList, queen_d4, wqueen);   
    gen_bishop_moves(moveList, queen_d4, wqueen);   
    print_moveList(moveList);

    moveList.clear();
    
}

void test_movegen(){
    vector<Board> moveList;
    cout << "Test for movegen: " << endl;

    cout << "Test starting position" << endl;
    Board starting_white_pos = Board("rnbqkbnr/pppppppp/8/8/8/N7/PPPPPPPP/R1BQKBNR b KQkq - 0 1");
    movegen(moveList, starting_white_pos);  
    print_moveList(moveList);

    cout << moveList.size() << endl;

    moveList.clear();
}

void test_starting(){
    vector<Board> moveList;
    Board starting_white_pos = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    cout << "King" << endl;
    gen_king_moves(moveList, starting_white_pos, wking);
    print_moveList(moveList);
    moveList.clear();

    cout << "Queen" << endl;
    gen_rook_moves(moveList, starting_white_pos, wqueen);
    gen_bishop_moves(moveList, starting_white_pos, wqueen);
    print_moveList(moveList);
    moveList.clear();

    cout << "Rook" << endl;
    gen_rook_moves(moveList, starting_white_pos, wrook);
    print_moveList(moveList);
    moveList.clear();

    cout << "Bishop" << endl;
    gen_bishop_moves(moveList, starting_white_pos, wbishop);
    print_moveList(moveList);
    moveList.clear();

    cout << "Knight" << endl;
    gen_knight_moves(moveList, starting_white_pos, wknight);
    print_moveList(moveList);
    moveList.clear();

    cout << "Pawn" << endl;
    gen_pawn_moves(moveList, starting_white_pos, wpawn);
    print_moveList(moveList);
    moveList.clear();


}


int perft(int depth, Board posistion){
    vector<Board> moveList;
    bitboard nodes = 0;

    if(depth == 0)
        return 1;
    
    movegen(moveList, posistion);

    for(Board b : moveList){
        nodes += perft(depth - 1, b);
    }
    
    return nodes;
}

int main(){
    // test_gen_king_moves();
    //test_gen_knight_moves();
    //test_gen_pawn_moves();
    //test_gen_rook_moves();
    //test_gen_bishop_moves();
    // test_gen_queen_moves();
    // test_movegen();
    // test_starting();


    cout << endl << "PERFT" << endl;
    Board starting_white_pos = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    int count = perft(3, starting_white_pos);
    cout << "Count: " << count << endl;    

}