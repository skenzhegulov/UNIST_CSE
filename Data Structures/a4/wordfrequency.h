#ifndef WORDFREQUENCY_H
#define WORDFREQUENCY_H

#include "BST.h"

#include <string>
#include <iostream>

/** 
 * Assignment 4 for CSE221 Data Structures
 *
 * 2014. 10. 28
 *
 * Won-Ki Jeong
 *
 */

typedef TreeNode< std::string, int > WordFreqElem;
typedef BST< WordFreqElem > Dictionary;

// WordFrequency class
class WordFrequency {
public:
	WordFrequency();
	~WordFrequency();
	
	// Read the text file and create dictionary
	void ReadText(const char* filename);
		
	// Find the frequency of word.
	// If not found, return 0.
	int GetFrequency(const std::string word);
	
	// Search word in dictionary and increase its frequency by 1.
	// If not found, insert word to dictionary and set the frequency as 1.
	void IncreaseFrequency(const std::string word);
	
	// Print frequency of all words in alphabetical order.
	void PrintAllFrequency();
	
private:
	
	// dict is BST
	Dictionary dict;
};

#endif
