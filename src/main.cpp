#include "uci.h"
#include "board.h"
#include "movegen.h"

#include <iostream>

using namespace std;

int main(){
    //uci();
      Board chess_board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
      
      // Board board_1e4 = Board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
      chess_board.printBoard();
      Board chess_board2 = Board(chess_board, wknight, 262208);

      chess_board2.printBoard();
      // board_1e4.printBoard();

      // cout << "Needed bytes for every possible move from the start position: "<< sizeof(Board) * 20 << endl;
      return 0;
}
