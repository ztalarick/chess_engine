/*
  Author: Zachary Talarick
  Date: 03/28/2021

  This file provides methods to implement the Universal Chess Interface
  UCI is a protocol for a chess engine to communicate with a GUI
  A GUI will communicate with the engine using STDIN and the engine will respond
  with STDOUT

*/

#include <iostream>
#include <sstream>
#include <string>
#include "uci.h"


using namespace std;


//loop forever reciving STDIN
void uci(){
  string cmd;
  while(cin >> cmd){
    if(cmd.compare("uci") == 0){
      cout << "id name Straight Six" << endl;
      cout << "id author Zachary Talarick" << endl;

      // set initial options
      // cout << "option name Hash type spin default 1 min 1 max 128" << endl;

      cout << "uciok" << endl;
    }

    if(cmd.compare("isready") == 0){
      cout << "readyok" << endl;
    }
    
  }
}
