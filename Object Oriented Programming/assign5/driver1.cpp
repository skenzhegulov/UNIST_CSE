#include "ExtendableArray.h"
#include <iostream>
using namespace std;

void stuff_20(ExtendableArray arr)
{
  for (int i=0; i < 20; i++) {
    arr[ i ] = i;
  }

  cout << arr << endl; // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
}

int main() { 
  ExtendableArray a1;
  cout<<"check 1"<<endl;
  for (int i=0;i<20;i++){
    a1[i] = i;
  }
  cout << a1 << endl; //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
  if(1){
  	cout<<"check 2"<<endl;
      ExtendableArray a2;
      for (int i=0;i<10;i++)
        a2[i+5] = a1[i];
	cout<<"check 3"<<endl;
      cout << a2 << endl; //0 0 0 0 0 0 1 2 3 4 5 6 7 8 9

      a1 = a2;

      for (int i=0;i<10;i++)
        a2[i] = i;
	cout<<"check 4"<<endl;
      cout << a1 << endl; //0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
      cout << a2 << endl;  //0 1 2 3 4 5 6 7 8 9 5 6 7 8 9
  }
	cout<<"check 5"<<endl; 
  cout << a1 << endl; //0 0 0 0 0 0 1 2 3 4 5 6 7 8 9

  ExtendableArray a3;

  a3[0] = 1;

  cout<<"check 6"<<endl;

  cout << a3 << endl; // 1 0 0 0 0

  stuff_20(a3);
  cout<<"check 7"<<endl;
  cout << a3 << endl; // 1 0 0 0 0

  cout << a3[2147483647] << endl; // 0

  return 0;
}

