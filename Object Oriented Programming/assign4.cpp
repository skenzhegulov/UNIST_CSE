#include<iostream>

using namespace std;

class AssignmentScores
	{
		private:
		static int totalSum; // total sum of assignment scores for class
		static int overallMax; // max assignment score for class
		static int overallMin; // min assignment score for class
		string name; // name of a student
		int num; // number of assignments submitted by this student
		int sum; // sum of assignment scores of this student
		int* scores; // array of assignment scores of this student

		public:
		static int getTotalSum(){ return totalSum; }// get total sum of scores for class
		static int getOverallMin(){ return overallMin; }// get overall min score
		static int getOverallMax(){ return overallMax; }// get overall max score

		AssignmentScores operator=(const AssignmentScores &right); // overloaded operator
		AssignmentScores(){
			name="";
			num=0;
			sum=0;
			scores=NULL;
		} // constructor
		AssignmentScores(const AssignmentScores &assignScore); // copy constructor
		~AssignmentScores(){
			delete scores;
		}// destructor

		void setName(string name){
			this->name = name;
		}// set name of this student
		string getName(){
			return name;
		}// get name of this student
		void setNum(int num){
			this->num = num;
		}// set num of assignments submitted by this student
		int getSum(){
			return sum;
		}// get sum of scores for this student
		int getMax(){
			int Max = 0;
			for(int i=0; i<num; i++) Max = max(Max, scores[i]);
			return Max;
		}// get max scores of this student
		int getMin(){
			int Min = 100;
			for(int i=0; i<num; i++) Min = min(Min, scores[i]);
			return Min;
		}// get min scores of this student
		void setScores(int scores[], int num){
			this->scores = scores;
			this->num = num;
			for(int i=0; i<num; i++) {
				// calculating total sum and overall min, max scores
				totalSum += scores[i];
				overallMin = min(overallMin, scores[i]); 
				overallMax = max(overallMax, scores[i]);
				// calculating sum of scores for this student
				sum += scores[i];
			}
		}// set assignment scores of this student
};
// initializing static variables
int AssignmentScores::totalSum = 0;
int AssignmentScores::overallMin = 100;
int AssignmentScores::overallMax = 0;

int n, k;
int *b;
string s;

int main(){
	cin>>k;  // getting the number of students
	AssignmentScores ind[k]; // creating objects for each student
	for(int i=0; i<k; i++) {
		// getting student data
		cin>>s>>n;  
		b=new int[n]; 
		for(int j=0; j<n; j++) cin>>b[j];
		// implementing data to object
		ind[i].setName(s);
		ind[i].setScores(b, n);
	}
	// writing on screen overall and each student's sum, max and min scores
	cout<<AssignmentScores::getTotalSum()<<endl<<AssignmentScores::getOverallMax()<<endl<<AssignmentScores::getOverallMin()<<endl;
	for(int i=0; i<k; i++) cout<<ind[i].getName()<<" "<<ind[i].getSum()<<" "<<ind[i].getMax()<<" "<<ind[i].getMin()<<endl;
return 1;
}

