#include "wordfrequency.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

/** 
 * Assignment 4 for CSE221 Data Structures
 *
 * 2014. 10. 28
 *
 * Won-Ki Jeong
 *
 */

WordFrequency::WordFrequency()
{
	// ToDo
}

WordFrequency::~WordFrequency()
{
	// ToDo
}

void WordFrequency::ReadText(const char* filename)
{
	std::string sub;
	std::ifstream Text(filename);
	if (Text.is_open()) {
	 while(Text>>sub) {
	  std::transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
	  std::string ss = "";
	  for(int i=0; i<sub.size(); i++) 
	   if((int(sub[i])>=97 && int(sub[i])<=122)) ss+=sub[i];
	  IncreaseFrequency(ss); 	  
	 }
	 Text.close();
	}
}

int WordFrequency::GetFrequency(const std::string word)
{
	// ToDo
	if(dict.Search(word)) return (dict.Search(word))->val;
	return 0;
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
	// ToDo
	int v = 1;
	if(dict.Search(word)) v += (dict.Search(word))->val;
	dict.Insert(word, v); 
}

void WordFrequency::PrintAllFrequency()
{
	// ToDo
	dict.PrintInorder();
}

