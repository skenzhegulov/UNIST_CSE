#ifndef BST_H
#define BST_H

//#include "wordfrequency.h"

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

/*
 *
 *  Class Definitions
 *
 */ 

template <class KeyType, class ValType>
class TreeNode
{
public:
	typedef KeyType ktype;
	typedef ValType vtype;
	
	// constructor
	TreeNode();
	
	// constructor
	TreeNode(KeyType k, ValType v);
	
	~TreeNode();
	
	KeyType key;
	ValType val;
	
	TreeNode* left;
	TreeNode* right;
};


//
// Binary Search Tree class
//
// Note that key type must have "<" and ">" operators so that
// you can compare the order of keys using < or >.
//
template <class TreeNodeType> 
class BST
{
	// WordFrequency class can access BST's private variables
	friend class WordFrequency;
	
public:
	typedef typename TreeNodeType::ktype KeyType;
	typedef typename TreeNodeType::vtype ValType;
	
	// constructor
	BST();
	
	// destructor
	~BST();
	
	// Search the node having key value k.
	// If not found, return NULL
	TreeNodeType* Search(const KeyType k);
	
	// Insert (k,v) pair to BST.
	// If a node with the key k exists, then replace
	// its value with v.
	void Insert(const KeyType k, const ValType v);
	
	// Remove a node having the key value k.
	// If not found, do nothing.
	bool Remove(const KeyType k);
	
	// Print key : value in ascending order (key is increasing)
	// by doing inorder traversal
	void PrintInorder();
	
private:
	void Print(TreeNodeType *curr);

	void Destructor(TreeNodeType *curr);
		
	TreeNodeType* root;
};


/*
 *
 *  TreeNode Class Implementations
 *
 */ 

template <class KeyType, class ValType>
TreeNode<KeyType, ValType>::TreeNode()
{
	left = right = NULL;
}

template <class KeyType, class ValType>
TreeNode<KeyType, ValType>::TreeNode(KeyType k, ValType v)
{
	left = right = NULL;
	key = k;
	val = v;
}

template <class KeyType, class ValType>
TreeNode<KeyType, ValType>::~TreeNode()
{
	if(left) delete left;
	if(right) delete right;
}


/*
 *
 *  BST Class Implementations
 *
 */ 
template <class TreeNodeType> 
BST<TreeNodeType>::BST()
{
	// ToDo
	root = NULL;
}

template <class TreeNodeType> 
BST<TreeNodeType>::~BST()
{
	// ToDo	
	//if (this->root != NULL) Destructor(this->root);
	root = NULL;
	delete root;
}

template <class TreeNodeType>
void BST<TreeNodeType>::Destructor(TreeNodeType *curr)
{
	if(curr->left) Destructor(curr->left);
	if(curr->right) Destructor(curr->right);
	if(curr == this->root) std::cout<<"Destructor BST is OK!\n";
	delete curr;
}

template <class TreeNodeType> 
TreeNodeType* 
BST<TreeNodeType>::Search(const KeyType k)
{
	// ToDo
	if (this->root == NULL) { return NULL; }
	TreeNodeType *temp = this->root;
	while(k != temp->key)
	 if(k>temp->key) {
	  if(!temp->right) { return NULL; }
	  temp = temp->right;
	 } else {
	  if(!temp->left) { return NULL;}
	  temp = temp->left;
	 } 
	return temp;
}

template <class TreeNodeType>
void 
BST<TreeNodeType>::Insert(const KeyType k, const ValType v)
{
	// ToDo
	TreeNodeType *temp;
	temp = new TreeNodeType;
	temp->key = k;
	temp->val = v;
	if(this->root == NULL) this->root = temp; else {
	 TreeNodeType *curr = this->root;
	 while(true) 
	  if(k == curr->key) {
	   curr->val = v;
	   break;
	  } else
	  if(k>curr->key) {
	   if(!curr->right) { 
	    curr->right = temp;
	    break;
	   }
	   curr = curr->right;
	  } else {
	   if(!curr->left) {
	    curr->left = temp;
	    break;
	   }
	   curr = curr->left;
	  }
	}
}

template <class TreeNodeType>
bool 
BST<TreeNodeType>::Remove(const KeyType k)
{
	// ToDo
	if(this->root == NULL) return false;
	TreeNodeType *temp = root;
	TreeNodeType *parent = NULL;
	bool left;
	std::cout<<"Searching for: "<<k<<"\n";
	while(temp->key != k) 
	 if(k > temp->key) {
	  if(!temp->right) return false;
	  parent = temp;
	  temp = temp->right;
	  left = false;
	 } else {
	  if(!temp->left) return false;
	  parent = temp;
	  temp = temp->left;
	  left = true;
	 }

	if(!temp->left && !temp->right) {
	 if(parent) {
	  if(left) parent->left = NULL; else parent->right = NULL;
	  delete temp;
	 } else temp = NULL;
	} else

	if(!temp->left) {
	 if(parent) {
	  if(left) parent->left = temp->right; else parent->right = temp->right;
	 } else root = temp->right;
	 temp = NULL;
	 delete temp;
	} else

	if(!temp->right) {
	 if(parent) {
	  if(left) parent->left = temp->left; else parent->right = temp->left;
	 } else root = temp->left;
	 temp = NULL;
	 delete temp;
	} else {
	 TreeNodeType *curr = temp->right;
	 TreeNodeType *curr_p; 
	 curr_p = NULL;

	 while(curr->left) {
	  curr_p = curr;
	  curr = curr->left;
	 }
	 temp->val = curr->val;
	 temp->key = curr->key;
	 if(curr_p) {
	  curr_p->left = curr->right;
	 } else {
	  temp->right = curr->right;
	 }
	 curr = NULL;
	 delete curr;
	}	 
	return true;
}


template <class TreeNodeType>
void 
BST<TreeNodeType>::PrintInorder()
{
	// ToDo
	//LVR
	if(!root) return;
	TreeNodeType *temp = root;
	Print(temp);
}

template <class TreeNodeType>
void BST<TreeNodeType>::Print(TreeNodeType *curr) 
{
	if(curr->left) Print(curr->left);
	std::cout<<curr->key<<" : "<<curr->val<<std::endl;
	if(curr->right) Print(curr->right);
}

#endif
