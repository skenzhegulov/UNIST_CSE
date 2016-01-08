#include<iostream>
#include<string>
#include<vector>

using namespace std;

//Creating variables according to input data: 
//Array of "number" stores number of problems solved by each contestant
//Array of "penalty" stores penalty time of each constestant
//Array of "solved" indicates whether problem solved or not by some contestant
//Array of "extra_p" stores extra penalty for incorrect submission to each problem of some contestant
//Array of "part" indicates whether this team participated or not
//String "s" is used to check blank lines
int N, T, t=0, i=0, contestant, problem, Time, number[101], penalty[101], solved[101][11], extra_p[101][11], part[101]; 
char L;
string ss;
vector <string> s;

//Function of sorting and output
void sort() {
	int n=0, a[101], b[101], c[101]; //Creating variables to store data for sorting
	//Filling variables with necessary data
	for(int i=1; i<101; i++)
	 if (part[i]) {
		a[n]=number[i];
		b[n]=penalty[i];
		c[n]=i;
		n++;
	 }
	//Bubble sort
	for(int i=0; i<n-1; i++)
	 for(int j=i+1; j<n; j++)
	  if (a[i]<a[j] || a[i]==a[j] && b[i]>b[j] || a[i]==a[j] && b[i]==b[j] && c[i]>c[j]) { 
		swap(a[i],a[j]);
		swap(b[i],b[j]);
		swap(c[i],c[j]);
	  }
	//Output
	if (t>1 && n) cout<<endl;
	for(int i=0; i<n; i++) cout<<c[i]<<" "<<a[i]<<" "<<b[i]<<endl;
 return;
}

int main(){
 //Reading input data
 cin>>T;
 getline(cin, ss);
 while (getline(cin,ss)) {
	s.push_back(ss);
 }
 N=s.size();
 for (int i=0; i<N; i++) {
	//Checking line blank or not 
	if (s[i].empty()) {
		if (t>0) sort();//Blank line and non-zero "t" indicates that one test case is inputted and we sort data and output data
		//Preparing variables for a new test case
		memset(solved, 0, sizeof(solved));
		memset(penalty, 0, sizeof(penalty));
		memset(extra_p, 0, sizeof(extra_p));
		memset(number, 0, sizeof(number));
		memset(part, 0, sizeof(part));
		t++;
	} else {
		//Getting data from string "s" and converting to int
		int j=0;
		contestant=0;
		problem=0;
		Time=0;
		while (s[i][j]!=' ') { contestant=contestant*10+(s[i][j]-'0'); j++; } //for contestant
		while (s[i][j]==' ') j++;
		while (s[i][j]!=' ') { problem=problem*10+(s[i][j]-'0'); j++;} //for problem
		while (s[i][j]==' ') j++;
		while (s[i][j]!=' ') { Time=Time*10+(s[i][j]-'0'); j++;} //for Time
		L=s[i][s[i].size()-1]; //for L
		part[contestant]=1; //Indicating that this contestant took a part
		//Solving our problem
		if (L=='C' && !solved[contestant][problem]) { //Correct submission
			solved[contestant][problem]=1; //Indicating that contestant solved this problem
			penalty[contestant]=penalty[contestant]+Time+extra_p[contestant][problem]; //Calculating penalty time
			number[contestant]++; //Increasing the number of solved problems
		} else
		if (L=='I') { //Incorrect submission
			extra_p[contestant][problem]+=20; //Adding extra penalty time for incorrect submission
		}
	}
 }
 sort(); //Sorting and writing on the screen remaining data
 return 0;
}
