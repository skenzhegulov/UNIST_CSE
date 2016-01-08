#include "maze.h"
#include <iostream>

int main(int argc, char** argv)
{
	// Stack test
	Stack<int> s;
	s.Push(10);
	s.Push(20);
	s.Push(30);
	s.Push(40);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(7);
	s.Push(8);
	while(!s.IsEmpty())
	{
		printf("%d\n", s.Top());
		s.Pop();
	}
	printf("-----\n");
	
	// Queue test
	Queue<int> q;
	q.Enque(10);
	q.Enque(20);
	q.Enque(30);
	q.Enque(40);	
	q.Enque(1);
	q.Enque(2);
	q.Enque(3);
	q.Enque(4);
	q.Enque(5);
	q.Enque(6);
	q.Enque(7);
	q.Enque(8);
	while(!q.IsEmpty())
	{
		printf("%d\n", q.Front());
		q.Deque();
	}
	printf("-----\n");

	// Maze test
	path(argv[1]);
		
	return 0;
}
