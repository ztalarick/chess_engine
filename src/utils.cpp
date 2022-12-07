#include "utils.h"

#include <vector>
#include <iostream>

using namespace std;


void printBitboard(bitboard b){
  vector<bitboard> squares;
  for(int j = 1; j < 65; j++){
    squares.push_back( (b & 1) );
    b = b >> 1;
  }
  reverse(squares.begin(), squares.end());
  for(int j = 1; j < 65; j++){
    cout << squares.at(j - 1) << ((j % 8 == 0) ? '\n' : ' ');
  }
}

//this function is to split a fen string by a delimeter
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