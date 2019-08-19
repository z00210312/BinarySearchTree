// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by	JIA SHIN TSENG
// Modified day	2/23/2016

//////////////////////////// BinaryNode.h starts here functions ////////////////////////////////////////////

#ifndef _BINARY_NODE
#define _BINARY_NODE
#include <iomanip>

template<class ItemType>
class BinaryNode
{   
private:
	ItemType              item;         // Data portion
	ItemType              m_name;
	float                 m_gpa;
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(const ItemType & anItem)	{item = anItem; leftPtr = 0; rightPtr = 0;}
	BinaryNode(const ItemType & anItem, 
		       const ItemType & name, 
		       const float gpa) {item = anItem; m_name = name; m_gpa = gpa; leftPtr = 0; rightPtr = 0;}
	BinaryNode(const ItemType & anItem, 
		       BinaryNode<ItemType>* left, 
			   BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
	// accessors
	void setItem(const ItemType & anItem) {item = anItem;}
	void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
	// mutators
	ItemType getItem() const	 {return item;}
	ItemType getName() const { return m_name; }
	float getgpa() const { return m_gpa; }
	void getDetail() {
		cout << left << setw(5) << item;
		cout << setw(25) << m_name;
		cout.setf(ios::fixed, ios::floatfield);
		cout << right << setw(2) << setprecision(1) << m_gpa << endl;
	}
	BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
	BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 

//////////////////////////// BinaryNode.h ends here functions ////////////////////////////////////////////