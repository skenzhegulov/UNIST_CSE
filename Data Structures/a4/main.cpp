
#include "wordfrequency.h"
#include <string>

using namespace std;

int main()
{
	WordFrequency freqChecker;
	
	freqChecker.ReadText("input.txt");
	
	cout << "# of occurrence of word 'chance' : " << freqChecker.GetFrequency("chance") << endl;
	
	cout << "Print all result" << endl;
	freqChecker.PrintAllFrequency();
	
	return 0;
}