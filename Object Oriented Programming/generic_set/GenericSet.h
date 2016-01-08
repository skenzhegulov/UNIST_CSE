#ifndef __GENERICSET_H__
#define __GENERICSET_H__

#define MAX_ITEMS 20

#include <iostream>
using namespace std;

template <class ItemType> class GenericSet
{
        protected:
                int size;
                ItemType values[MAX_ITEMS];

        public:
                // Default Constructor
                // Post condition: an Empty generic set is created
                GenericSet();

                // Insert function
                virtual void Insert(ItemType item)=0;

                // Delete function
                virtual void Delete(ItemType item)=0;

                // Clear function
                // Post condition: all items are removed from the generic set, and the
                //                 size of the generic set becomes 0.
                void Clear();

                // GetSize function
                // Return value is the number of items in the generic set
                int GetSize();

                // IsFull function
                // Return true if there is no more space in the generic set,
                //        false otherwise.
                bool IsFull();

                // IsEmpty function
                // Return true if the generic set is empty,
                //        false otherwise.
                bool IsEmpty();

                friend std::ostream& operator<<(std::ostream& out, const GenericSet& s){
                        out << "{";
                        for(int i=0;i<s.size;i++){
                                out << s.values[i] ;
                                if(i < s.size-1) out << ", ";
                        }
                        out << "}";
                        return out;
                }
};

//creating derived Set class
template <class ItemType> class Set : public GenericSet<ItemType>{
	public:
		virtual void Insert(ItemType value);
		virtual void Delete(ItemType value);
	};

//creating derived Beg class
template <class ItemType> class Bag : public GenericSet<ItemType>{
	public:
		virtual void Insert(ItemType value);
		virtual void Delete(ItemType value);
	};

//GenericSet class functions
template <class ItemType> GenericSet<ItemType>::GenericSet() {this->size = 0;}
template <class ItemType> void GenericSet<ItemType>::Clear() {this->size = 0;}
template <class ItemType> int GenericSet<ItemType>::GetSize() {return this->size;};
template <class ItemType> bool GenericSet<ItemType>::IsFull() {return this->size == MAX_ITEMS;}
template <class ItemType> bool GenericSet<ItemType>::IsEmpty() {return this->size == 0;}


//Derived classes' functions

//Insert functions
//For Set class
template<class ItemType> void Set<ItemType>::Insert(ItemType value){
	if (this->IsFull()) {
		throw "Set Exception: No more space";
		return;
	}
	for (int i = 0; i < this->size; i++)
		if (this->values[i] == value) return;
	this->values[this->size] = value;
	this->size++;
}
//For Bag class
template<class ItemType> void Bag<ItemType>::Insert(ItemType value){
	if (this->IsFull()) {
		throw "Bag Exception: No more space";
		return;
	}
	this->values[this->size] = value;
	this->size++;
}

//Delete functions
//For Set class
template<class ItemType> void Set<ItemType>::Delete(ItemType value){
	for (int i = 0; i < this->size; i++)
		if (this->values[i] == value) {
			this->size--;
			for (int j = i; j < this->size; j++) this->values[j] = this->values[j+1];
			return;	
		}
	throw "Set Exception: Not found";
}
//For Bag class
template<class ItemType> void Bag<ItemType>::Delete(ItemType value){
	for (int i = 0; i < this->size; i++)
		if (this->values[i] == value) {
			this->size--;
			for (int j = i; j < this->size; j++) this->values[j] = this->values[j+1];
			return;	
		}
	throw "Bag Exception: Not found";
}

#endif

