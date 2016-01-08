//Including needed libraries
#include<iostream>      //To use basic C++ functions as 'cin'
#include<string>        //To use data type of strings
#include<algorithm>     //To use 'tolower' function

using namespace std;

//Declaring global variables
string c[100], s;       //Variables for our grids and words 
int n,m,k,K,T,t;        //Variables for number of cases, grids and etc
bool b;                 //Variable indicating whether word is found or not

//Function for checking whether word is at given positions or not
int solve(string s, int x, int y){                                                              //Given word, and positions from which we start checking
        int d1, d2, d3, d4, d5, d6, d7, d8, l=s.size();                                         //Variables for directions and length of the word
        d1=d2=d3=d4=d5=d6=d7=d8=1;                                                              //Initially we assume that word can be found in all directions
        for(int i=1; i<l; i++){                                                                 //Checking letter by letter, dx=1 (x=[1..8]) means that word can be found in that direction
                if (d1 && x+i<=n && tolower(c[x+i][y])==tolower(s[i])) true;                    //Checking direction to the downward
                 else d1=0;                                                                     //Word is not in that direction
                if (d2 && x-i>=0 && tolower(c[x-i][y])==tolower(s[i])) true;                    //Checking direction to the upward
                 else d2=0;                                                                     //Word is not in that direction
                if (d3 && y+i<=m && tolower(c[x][y+i])==tolower(s[i])) true;                    //Checking direction to the rightward
                 else d3=0;                                                                     //Word is not in that direction
                if (d4 && y-i>=0 && tolower(c[x][y-i])==tolower(s[i])) true;                    //Checking direction to the leftward
                 else d4=0;                                                                     //Word is not in that direction
                if (d5 && x+i<=n && y+i<=m && tolower(c[x+i][y+i])==tolower(s[i])) true;        //Checking direction to the right-downward diagonal
                 else d5=0;                                                                     //Word is not in that direction
                if (d6 && x+i<=n && y-i>=0 && tolower(c[x+i][y-i])==tolower(s[i])) true;        //Checking direction to the left-downward diagonal
                 else d6=0;                                                                     //Word is not in that direction
                if (d7 && x-i>=0 && y+i<=m && tolower(c[x-i][y+i])==tolower(s[i])) true;        //Checking direction to the right-upward diagonal
                 else d7=0;                                                                     //Word is not in that direction
                if (d8 && x-i>=0 && y-i>=0 && tolower(c[x-i][y-i])==tolower(s[i])) true;        //Checking direction to the left-upward diagonal
                 else d8=0;                                                                     //Word is not in that direction
        }
        return d1+d2+d3+d4+d6+d5+d7+d8; //If the sum is zero then word is not found in that position, otherwise it's found in one of the given directions
}

int main(){
 cin>>T;                                                                                        //Reading number of cases
 for(int t=0; t<T; t++){
        cin>>n>>m;                                                                              //Reading number and length of the grids
        for(int i=0; i<n; i++) cin>>c[i];                                                       //Reading grids
        cin>>K;                                                                                 //Reading number of words
        for(int k=0; k<K; k++) {                                                                //Starting to work on words one-by-one
                cin>>s;                                                                         //Reading next word
                b=0;                                                                            //Indicating that word is not found
                for(int i=0; i<n; i++)                                                          //Going through the grids
                 if (b) break; else                                                             //If word is found we will stop searching
                  for(int j=0; j<m; j++)                                                        //Going through the grids
                   if (tolower(c[i][j])==tolower(s[0]))                                         //If the letter at that position is the same as the first letter of the given word then 
                    if (solve(s,i,j)) {                                                         //Start function which indicates whether word is found or not
                        b=1;                                                                    //If we find a given word we mark it as found
                        cout<<i+1<<" "<<j+1<<endl;                                              //Immediately writing the position of the first letter
                        break;                                                                  //And stop searching
                    }
        }
  cout<<endl;
 }
 return 0;                                                                                      //Ending program
}
