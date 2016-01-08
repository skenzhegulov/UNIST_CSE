#include<iostream>

#define MAXDIGITS 10

using namespace std;

class ReversibleInteger {
	private:
		char digits[MAXDIGITS]; /* represent the number */
		int lastdigit; /* index of high-order digit */
	public:
		int n; // number of digits in our number
		void setNumber(unsigned v){ //function to convert the number to char array
			n=0;
 			while (v){
				digits[n]=char(v%10+'0');
				v/=10;
				n++;
			}
		}
		ReversibleInteger(unsigned nn=0){ n=nn;} //constructor
		ReversibleInteger reverse(){ //function which reverses our char array into new one
			ReversibleInteger result;
			result.n = n;
			for (int i=n-1; i>=0; i--) result.digits[n-i-1]=digits[i];
			return result;
		}
		ReversibleInteger add(ReversibleInteger arg){ //returns sum of two numbers (original and reversed)
			ReversibleInteger result;	      // arg stores reversed array of our number
			result.setNumber(getValue()+arg.getValue());
			return result;
		}
		unsigned getValue(){ // returns the integer value of this object
			unsigned result=0;
			for (int i=n-1; i>=0; i--) result=result*10+int(digits[i]-'0');
			return result;
		}
		bool isPalindrome(){ // returns true if this integer is a palidrome
			for (int l=0, r=n-1; l<r; l++, r--) 
				if (digits[l]!=digits[r]) return false;
			return true;
		}
};

int N, j; //N is the number of test cases and j is just pointer
unsigned x; //x is the number given in each test cases

int main(){
 ReversibleInteger ans; //creating class variable which will store the answer
 cin>>N; 
 for(int i=0; i<N; i++) {
	cin>>x;
	ans.setNumber(x); //setting from our number char array
	for(j=1; j<=1001 && !ans.isPalindrome(); j++) ans=ans.add(ans.reverse()); //getting the the sum until the number is not palindrome
	if (j<1001) cout<<j-1<<" "<<ans.getValue()<<endl; //writing the answer
 }
 return 0;
}
