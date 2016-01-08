#include "minheap.h"

/** 
 * Assignment 5 for CSE221 Data Structures
 *
 * 2014. 11. 17
 *
 */

using namespace std;
// Destructor
MinHeap::~MinHeap()
{
	// ToDo
	//cout<<"Destr: ";
	delete [] heapArray;
	delete [] mapVidxToArray;
	//cout<<"~MinHeap\n";
}

void
MinHeap::Swap(unsigned int i1, unsigned int i2)
{	
	unsigned int v = heapArray[i1].vidx;
 	heapArray[i1].vidx = heapArray[i2].vidx;
	heapArray[i2].vidx = v;

	double d = heapArray[i1].dist; 
	heapArray[i1].dist = heapArray[i2].dist;
	heapArray[i2].dist = d; 

 	mapVidxToArray[heapArray[i1].vidx] = i1;
 	mapVidxToArray[heapArray[i2].vidx] = i2;
}

void 
MinHeap::Push(const heapElem& e)
{
	// ToDo
	//cout<<"Push: "<<e.vidx<<endl;
	this->size++;
	(this->heapArray[this->size]).vidx = e.vidx;
	(this->heapArray[this->size]).dist = e.dist;
	mapVidxToArray[e.vidx] = size;
	Up(size);
}

void 
MinHeap::Up(unsigned int i1) {
	while(i1>1 && (this->heapArray[i1]).dist<(this->heapArray[i1/2]).dist) {
		Swap(i1,i1/2);
		i1 /= 2;
	}
	//cout<<"Up until: "<<i1<<endl;
}

const heapElem & 
MinHeap::Top()
{
	// ToDo
	//cout<<"Top!\n";
	return heapArray[1];
}

void 
MinHeap::Pop()
{	
	// ToDo
	//cout<<"Pop!\n";
	heapArray[1].vidx = heapArray[size].vidx;
	heapArray[1].dist = heapArray[size].dist;
	mapV[heapArray[1].v] = 1;	
	this->size--;
	Down(1);
}

void 
MinHeap::Down(unsigned int i1)
{
 	unsigned int i2 = i1;
 	if (i1*2<=size && (this->heapArray[i1*2]).dist<(this->heapArray[i2]).dist) i2 = i1*2;
 	if (i1*2+1<=size && (this->heapArray[i1*2+1]).dist<(this->heapArray[i2]).dist) i2 = i1*2+1;
 	if (i1!=i2) {
 	 Swap(i1,i2);
 	 Down(i2);
 	}
}

bool 
MinHeap::Modify(const heapElem &e)
{
	// ToDo
	//cout<<"Modify "<<endl;
	//cout<<mapVidxToArray[e.vidx]<<endl;
	//cout<<e.vidx<<" :: "<<e.dist<<endl;
	//cout<<(this->heapArray[mapVidxToArray[e.vidx]]).vidx<<" :: "<<(this->heapArray[mapVidxToArray[e.vidx]]).dist<<endl;
	if(e.dist<(this->heapArray[mapVidxToArray[e.vidx]]).dist) {
		//cout<<"success: "<<e.vidx<<endl;
		(this->heapArray[mapVidxToArray[e.vidx]]).dist = e.dist;
		Up(mapVidxToArray[e.vidx]);
		return true;
	}
	//cout<<"fail\n";
	return false;
}

bool MinHeap::IsEmpty()
{
	// ToDo
	if(!this->size) return true; else return false;
}
