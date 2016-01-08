#ifndef MAP_H
#define MAP_H

//
// Array-based stack and queue data structure
//
// CSE221 Fall 2014
//
// Won-Ki Jeong (wkjeong@unist.ac.kr)
//
#include <iostream>
#include <math.h>

using namespace std;

template<class type>
class Stack
{
public:
	// Default constructor 
	Stack(){
		this->capacity = 10;
		this->array = new type[capacity+1];
		this->top = 0;
	}

	// Destructor
	~Stack(){
	 	delete [] array;
	}

	// Return top element of stack
	type& Top(){
	 	return this->array[top];
	}
	
	void Push(const type& item){
		if (this->top == this->capacity) {
			type *temp_arr;
			this->capacity += 10;
			temp_arr = new type[capacity+1];
			for(int i=0; i<=top; i++) temp_arr[i] = this->array[i];
			this->array = temp_arr;
	 	}
	 	array[++this->top] = item;
	}
	
	void Pop(){
	 	if(this->top) top--;
	}
	
	bool IsEmpty() const{
	 	if(this->top) return false;
	 		else return true;
	}
	
private:
	// Data
	type *array;
	int capacity;
	int top;
};


template<class type>
class Queue
{
public:
	// Default constructor 
	Queue(){
		this->capacity = 10;
	 	this->array = new type[capacity];
	 	this->front = 0;
	 	this->rear = 0;
	}
	
	// Destructor
	~Queue(){
	 	delete [] array;
	}
	
	// Return top element of stack
	type& Front(){
	 	return this->array[front];
	}
	
	void Enque(const type& item){
	 	if (this->rear == this->capacity) {
	 		type *temp_arr;
	 		capacity = this->rear-this->front + 10;
	 		temp_arr = new type[capacity];
	 		for(int i=0; i<this->rear-this->front+1; i++) temp_arr[i] = array[i+this->front];
	 		this->rear -= this->front;
	 		this->front = 0;
	 		this->array = temp_arr;
	 	}
	 	this->array[rear++] = item;
	}
	
	void Deque(){
	 	this->front++;
	}
	
	bool IsEmpty() const{
	 	if(front == rear) return true;
	 		else return false;
	}
	
private:
	// Data
	type *array;
	int capacity;
	int front;
	int rear;
};


//
// Implementations
//


/** 
 * Read in map file, find the shortest path,
 * and print the path with the map 
 **/
void path(const char* map)
{
	freopen(map, "rt", stdin); 

	int n,m, X, Y, k;
	cin>>n>>m;
	int a[n][m];
	const int inf = 1000000;
	string s;
	Queue<int> x;
	Queue<int> y;

	for(int i=0; i<n; i++) {
		cin>>s;
		for(int j=0; j<m; j++) a[i][j] = s[j]-'0';
	}
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(a[i][j] == 1) a[i][j] = -1; else
			if(a[i][j] == 2) a[i][j] = 0, x.Enque(i), y.Enque(j); else
			if(a[i][j] == 3) a[i][j] = inf, X = i, Y = j; 
				else a[i][j] = inf;
	int i,j;
	while(a[X][Y] == inf) {
		i = x.Front(); x.Deque();
		j = y.Front(); y.Deque();
		k = a[i][j] + 1;
		if(i-1>=0 && a[i-1][j]==inf) {
			x.Enque(i-1);
			y.Enque(j);
			a[i-1][j] = k;
		} 
		if(i+1<n && a[i+1][j]==inf) {
		        x.Enque(i+1);
			y.Enque(j);
			a[i+1][j] = k;
		} 
		if(j-1>=0 && a[i][j-1]==inf) {
		        x.Enque(i);
			y.Enque(j-1);
			a[i][j-1] = k;
		} 
		if(j+1<m && a[i][j+1]==inf) {
		        x.Enque(i);
			y.Enque(j+1);
			a[i][j+1] = k;
		}
	}

	i = X;
	j = Y;
	k = a[i][j];
	while(true) {
		if(i-1>=0 && a[i-1][j]+1==k) i--; else
		if(i+1<n && a[i+1][j]+1==k) i++; else
		if(j-1>=0 && a[i][j-1]+1==k) j--; else
		if(j+1<m && a[i][j+1]+1==k) j++;
		k = a[i][j];
		if(!k) break;
		a[i][j] = -2;
	}

	a[X][Y] = 3;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++) {
			if(a[i][j] == -1) cout<<1; else
			if(a[i][j] == -2) cout<<'*'; else
			if(a[i][j] == 0) cout<<2; else
			if(a[i][j] == 3) cout<<3; else cout<<0;
		}
	cout<<endl;}
		
	return;
}

#endif
