#include "dijkstra.h"
#include <iostream>

/** 
 * Assignment 5 for CSE221 Data Structures
 *
 * 2014. 11. 17
 *
 */


int main()
{
	Dijkstra ds;
	
	ds.ReadGraph("input.txt");
	
	std::cout << "Shortest path between 0 and  : ";
	
	std::cout<< "Distance: " << ds.FindPath(0,6) <<std::endl;	
	return 0;
}

