#include <iostream>
using namespace std;
int main(){
  int num = 15;

  int bit = 0;
  while(num){
    cout << "Num1: " << num << endl;

    bit = num & -num;

    cout << "Bit: " << bit << endl;
    cout << "Num2: " << num << endl;

    num &= num - 1;
    cout << "Num3: " << num << endl;
    cout << endl;

  }

}
