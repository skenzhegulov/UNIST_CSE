#include "dijkstra.h"
#include<fstream>

/** 
  * Assignment 5 for CSE221 Data Structures
  *
  * 2014. 11. 17
  *
  */

using namespace std;

Dijkstra::~Dijkstra()
{
	delete [] adjList;
	delete [] headNode;
	delete [] prev;
}
	
void 
Dijkstra::ReadGraph(const char* file)
{
	ifstream Text(file);
	if (Text.is_open()) {
	 unsigned int n,m,x,y,z;
	 Text>>n>>m;
	 adjList = new graphNode[m+1];
	 headNode = new unsigned int[n+2];
	 prev = new unsigned int[n+2];
	 mheap = new MinHeap(n);        
	 for(unsigned int i=0; i<=n; i++) headNode[i] = -1; 
	 for(unsigned int i=0; i<m; i++) {
	  	Text>>x>>y>>z;
	  	adjList[i].idx = y;
	  	adjList[i].weight = z;
	  	adjList[i].next = headNode[x];
	  	headNode[x] = i;
	 }
	 Text.close();
	}
}

double 
Dijkstra::FindPath(const unsigned int v0, const unsigned int v1)
{	
	heapElem e, i;
	e.vidx = v0;
	e.dist = 0;
	mheap->Push(e);
	prev[v0] = v0;
	unsigned int j;
	double d = -1;
	while(!mheap->IsEmpty()) {
		i.vidx = (mheap->Top()).vidx;
		i.dist = (mheap->Top()).dist;
		mheap->Pop();
		if (i.vidx==v1) { d = i.dist; break; }
		j = headNode[i.vidx];
		while(j!=-1) 
		{
		 e.vidx = adjList[j].idx;
		 e.dist = adjList[j].weight + i.dist;
		 if (!mheap->IsInHeap(e)) {
		 	mheap->Push(e);
		 	prev[e.vidx] = i.vidx;
		 } else {
		   	if (mheap->Modify(e)) prev[e.vidx] = i.vidx;
		 }
		 j = adjList[j].next;
		}
	}
	if(d!=-1) {
		unsigned int n = 0;
		j = v1;
		while(prev[j]!=j){
			j = prev[j];
			n++;
		}
		unsigned int *path = new unsigned int[n];
		n = 0;
		j = v1;
		while(prev[j]!=j){
			n++;
			j = prev[j];
			path[n] = j;
		}
		for(unsigned int i=n; i>0; i--) cout<<path[i]<<" ";
		cout<<v1<<endl;
	} 
	return d;
}	
	
