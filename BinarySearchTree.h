// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by	JIA SHIN TSENG
// Modified day	2/23/2016
 
//////////////////////////// BinarySearchTree.h starts here functions ////////////////////////////////////////////

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// find the targeted entry in the nodes
	BinaryNode<ItemType>* _getEntry(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	bool insert(const ItemType & studentID, const ItemType & name, float gpa);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target);
};


///////////////////////// public function definitions ///////////////////////////

/*
Insert a node into the BST
*/

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}

/*
Insert a node into the BST with mulitiple variables
*/

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & studentID, const ItemType & name, float gpa)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(studentID, name, gpa);
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}

/*
Remove the node in the BST
*/

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

/*
Get an Entry from the BST
*/

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry)
{
	bool isSuccessful = false;
	rootPtr = _getEntry(rootPtr, anEntry, isSuccessful);
	return isSuccessful;
}  



//////////////////////////// private functions ////////////////////////////////////////////

/* 
Internal traverse for insert function
*/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	count++;
	if (!nodePtr)
	{
		nodePtr = newNodePtr;
	}
	else if (nodePtr->getItem() < newNodePtr->getItem())
	{
		_insert(nodePtr->getRightPtr(), newNodePtr);
		if (!nodePtr->getRightPtr())
			nodePtr->setRightPtr(newNodePtr);
	}
	else if (nodePtr->getItem() > newNodePtr->getItem())
	{
		_insert(nodePtr->getLeftPtr(), newNodePtr);
		if(!nodePtr->getLeftPtr())
			nodePtr->setLeftPtr(newNodePtr);
	}
	return nodePtr;
}  

/*
Internal traverse for remove function
*/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

/*
Internal traverse for get entry function
*/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_getEntry(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success)
{
	if (!nodePtr)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() == target)
	{
		success = true;
		cout << nodePtr->getItem() << " " << nodePtr->getName() << ", GPA: " << nodePtr->getgpa() << endl;;
	}
	else if (nodePtr->getItem() < target)
	{
		_getEntry(nodePtr->getRightPtr(), target, success);
	}
	else if (nodePtr->getItem() > target)
	{
		_getEntry(nodePtr->getLeftPtr(), target, success);
	}
	return nodePtr;
}

/*
Remove a node from the BST
*/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

/*
Remove the left most node from the BST
*/

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}
#endif

//////////////////////////// BinarySearchTree.h ends here functions ////////////////////////////////////////////