#include "ExtendableArray.h"
#include<iostream>

using namespace std;

//constructor
ExtendableArray::ExtendableArray() {	
	this->size = 5;
	this->arrayPointer = new int[this->size];
	for(int i=0; i<this->size; i++) this->arrayPointer[i] = 0;
}

//copy constructor
ExtendableArray::ExtendableArray( const ExtendableArray& other ){
	this->size = other.size;
	this->arrayPointer = new int[this->size];
	for(int i=0; i<this->size; i++) this->arrayPointer[i] = other.arrayPointer[i];
}

//destructor
ExtendableArray::~ExtendableArray(){ delete [] arrayPointer; }

//overloading with another object
ExtendableArray& ExtendableArray::operator=( const ExtendableArray& rhs ){
	if (this == &rhs) return *this;
	delete [] arrayPointer;
	this->size = rhs.size;
	arrayPointer = new int[this->size];
	for(int i=0; i<this->size; i++) arrayPointer[i] = rhs.arrayPointer[i];
	return *this; 
}

//getting element from array
ElementRef ExtendableArray::operator[]( int i ){
	ElementRef result(*this, i);
	return result;
}


//getting reference and pointer
ElementRef::ElementRef( ExtendableArray& theArray, int i ){
	this->index = i;
	this->intArrayRef = &theArray;
}

//copy constructor
ElementRef::ElementRef( const ElementRef& other ){ 
	this->index = other.index;
	this->intArrayRef->size = other.intArrayRef->size;
	this->intArrayRef->arrayPointer = new int [this->intArrayRef->size];
	for(int i=0; i<this->intArrayRef->size; i++) this->intArrayRef->arrayPointer[i] = other.intArrayRef->arrayPointer[i];
} 

//destructor but since it is reference we don't need to free any memory
ElementRef::~ElementRef(){ }

//overloading element of array by another object's element 
ElementRef& ElementRef::operator=( const ElementRef& rhs ){
	//when overloading element's index is beyond our array, we expand our array until that index
	if(this->index >= this->intArrayRef->size) {
		ExtendableArray newArray;
		newArray.size = this->index + 1;
		newArray.arrayPointer = new int [newArray.size];
		for(int i=0; i<newArray.size; i++)
			if(i < this->intArrayRef->size) newArray.arrayPointer[i] = this->intArrayRef->arrayPointer[i]; 
				else newArray.arrayPointer[i] = 0;
	this->intArrayRef->size = newArray.size;
	*this->intArrayRef = newArray;
	}
	//overloading process
	this->intArrayRef->arrayPointer[this->index] = rhs.intArrayRef->arrayPointer[rhs.index];
	return *this;
}

//overloading element of array by some value
ElementRef& ElementRef::operator=( int val ){
	//when overloading element's index is beyond our array, we expand our array until that index
	if(this->index >= this->intArrayRef->size){
		ExtendableArray newArray;
		newArray.size = this->index + 1;
		newArray.arrayPointer = new int [newArray.size];
		for(int i=0; i<newArray.size; i++)
			if(i < this->intArrayRef->size)	newArray.arrayPointer[i] = this->intArrayRef->arrayPointer[i];
				else newArray.arrayPointer[i] = 0;
		this->intArrayRef->size = newArray.size;
		*this->intArrayRef = newArray;
	}
	//overloading process
	this->intArrayRef->arrayPointer[this->index] = val;
	return *this;
}

//getting value of element
ElementRef::operator int() const {
	//when asking element's index beyond our array we return 0
	if(this->index < this->intArrayRef->size) return intArrayRef->arrayPointer[this->index]; 
}
