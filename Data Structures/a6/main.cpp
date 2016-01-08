#include "hashmap.h"
#include <iostream>
#include <fstream>

using namespace std;


typedef MapElem< std::string, unsigned int > HashElem;
typedef HashMap< HashElem > Dictionary;

Dictionary HTable;

void spellcheck(std::string s)
{
	std::cout << "> " << s;
	if(HTable.find(s)) cout<<" is in the dictionary\n"; 
	 else {
	 	cout<<" is NOT in the dictionary\n> "<<s<<" : ";
		int n = s.length();
		bool flag = false;
		for(int i=0; i<n; i++) {
			char t = s[i];
			for(char c='a'; c<='z'; c++) {
				s[i] = c;
				if(HTable.find(s)) {
				 	if (flag) cout<<", ";
				 	flag = true;
				 	cout<<s;
				}
			}
			s[i] = t;
	      	} 
	      	if(!flag) std::cout<<"no suggestion";
	      	cout<<"\n";
	      }
}


int main()
{
	// load dictionary
	char filename[] = "dictionary.txt";
	std::ifstream ifs(filename, std::ifstream::in);
	std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	std::transform(s.begin(), s.end(),
				   s.begin(), ::tolower);

	std::string token;	
	unsigned int len = s.length();
		
	for(int i=0; i<len; i++)
	{
		int ascii = s[i];
		
		if(ascii < 97 || ascii > 127) 
		{
			if(token.length() > 0) 
			{
				// ToDo
				// Insert token to hash map
				HTable.insert(token, 0);
				token.clear();
			}
			continue;
		}
		token.push_back(s[i]);
	}

	//
	// infinite loop to accept user input word
	//
	while(1)
	{
		std::string s;
		std::cout << "> ";
		std::cin >> s;
		if(s == "q") break;
		spellcheck( s );
	}
	
	
	return 0;
}
