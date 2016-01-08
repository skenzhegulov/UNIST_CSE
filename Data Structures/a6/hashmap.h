#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>

/** 
  * Assignment 6 for CSE221 Data Structures
  *
  * 2014. 12. 3
  *
  */

// Map element
template <class KeyType, class ValType>
class MapElem
{
public:
	typedef KeyType ktype;
	typedef ValType vtype;
	
	KeyType key;
	ValType val;
	
	MapElem* link;
};

bool inline operator==(std::string a, std::string b)
{
	if((a).compare(b) == 0) return true;
	return false;
}

//
// Hash Map data structure
//
template <class HashMapElemType> 
class HashMap
{
public:
	typedef typename HashMapElemType::ktype KeyType;
	typedef typename HashMapElemType::vtype ValType;
	
	// constructor
	HashMap(unsigned int c = 1000);
	
	// destructor
	~HashMap();
	
	// Modify below functions
	int size() { return mapsize; };
	
	bool isEmpty() { return (mapsize == 0); };
	
	// ToDo
	HashMapElemType* find(const KeyType k);
	
	void insert(const KeyType k, const ValType v);
		
	bool remove(const KeyType k);
	
	unsigned int hashfunction(const KeyType k);
	
	void print();
	
private:
	// Hash Table
	HashMapElemType** ht;
	
	unsigned int mapsize, capacity, divisor;
};



//
// - Implementation -
//

// constructor
template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
	// ToDo
	capacity = c;
	ht = new HashMapElemType*[capacity];
	for(int i=0; i<capacity; i++) ht[i] = NULL;
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
	// ToDo
	for(int i=0; i<capacity; i++)
		if(ht[i] != NULL) {
	  		HashMapElemType *prev = NULL;
	  		HashMapElemType *curr = ht[i];
	  		while(curr != NULL) 
	  		{
	   			prev = curr;
	   			curr = curr->link;
	   			delete prev;
	  		}	
	 	} 
	delete [] ht;
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{ 
	// ToDo
	unsigned int v = hashfunction(k);
	unsigned int i = v%capacity;
	if (ht[i] == NULL) return NULL; 
	 else {
	  	HashMapElemType *curr = ht[i];
	  	while(curr && curr->val != v) curr = curr->link;
	  	if (!curr) return NULL; 
	  		else return curr;
	      }
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
	// ToDo
	HashMapElemType *temp = new HashMapElemType;
	 temp->key = k;
	 temp->val = hashfunction(k);
	 temp->link = NULL;
	
	mapsize++;
	unsigned int i = (temp->val)%capacity;
	if (!ht[i]) ht[i] = temp;
	 else {
	  	HashMapElemType *curr = ht[i];
	  	while (curr->link) curr = curr->link;
	  	curr->link = temp;
	      }
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
	 // ToDo
	 unsigned int v = hashfunction(k);
	 unsigned int i = v%capacity;
	 if (ht[i]) {
	  	HashMapElemType *curr = ht[i];
	  	HashMapElemType *prev = NULL;
	  	while(curr->link && curr->val != v) 
	  	{
	   		prev = curr;
	   		curr = curr->link;
	  	}
	  	
	  	if(curr->key == k) {
	  		mapsize--;
	   		HashMapElemType *temp = curr->link;
	   		delete curr;
	   		if(!prev) ht[i] = temp;
	    			else prev->link = temp;
	  	}
	}
}

template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
	// ToDo	
	unsigned int v = 0;
	unsigned int p = 233;
	unsigned int f = 1;
	int n = k.size();
	for(int i=0; i<n; i++) {
		v = v*f + k[i];
		f *= p;
	}
	return v;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
	// ToDo
	for(int i=0; i<capacity; i++) 
		if(ht[i]) std::cout<<ht[i]->key<<":"<<ht[i]->val<<"  "<<i<<"\n";
}

#endif
