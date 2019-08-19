// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by	JIA SHIN TSENG
// Modified day	2/23/2016
 
//////////////////////////// BinaryTree.h starts here functions ////////////////////////////////////////////

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Stack.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree);
	virtual ~BinaryTree() { destroyTree(rootPtr); }
	BinaryTree & operator = (BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void indentedOrder(void visit(ItemType &)) const { int indentedCount = 0; _indentedorder(visit, rootPtr, indentedCount);}
	void preOrder() const { _preorder(rootPtr); }
	void inOrder() const  {_inorder(rootPtr);}
	void postOrder() const{_postorder(rootPtr);}
	void stackPreOrder();
	void stackInOrder();
	void stackPostOrder();
	void longestBranch();
	void setLongestBranch(BinaryNode<ItemType>* rootPtr, int & level, int count, Stack<BinaryNode<ItemType>*> &tempstack);

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool insert(const ItemType & studentID, const ItemType & name, float gpa) = 0;
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry) = 0;
	
	// get the root node
	BinaryNode<ItemType>* getRootNode() const {return rootPtr;}

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _indentedorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int indentedCount) const;
	void _preorder(BinaryNode<ItemType>* nodePtr) const;
	void _inorder(BinaryNode<ItemType>* nodePtr) const;
	void _postorder(BinaryNode<ItemType>* nodePtr) const;
	void _stackPreOrder(Stack<BinaryNode<ItemType>*> &tempstack);
	void _stackInOrder(Stack<BinaryNode<ItemType>*> &tempstack);
	void _stackPostOrder(Stack<BinaryNode<ItemType>*> &tempstack);
	void _longestBranch(BinaryNode<ItemType>* nodePtr, int branchCount, int & levelCount);
   
}; 

//////////////////////////////////////////////////////////////////////////

/*
Tree constructor
*/

template<class ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree<ItemType> & tree)
{
	rootPtr = copyTree(tree.getRootNode());
}

/*
Copy tree constructor
*/
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	if (!nodePtr)
	{
		return 0;
	}
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), nodePtr->getName(),nodePtr->getgpa());
	{
		if (nodePtr->getLeftPtr())
		{
			newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		}
		if (nodePtr->getRightPtr())
		{
			newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
		}
	}
    return newNodePtr;
}  

/*
Destructor a tree
*/

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

/*
Traverse for display the list in IndentedOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_indentedorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int indentedCount) const
{

	if (nodePtr != 0)
	{

		for (int i = 0; i < indentedCount; i++)
		{
			cout << "\t";
		}
		cout << indentedCount + 1 << ". ";
		ItemType item = nodePtr->getItem();
		visit(item);
		indentedCount++;
		_indentedorder(visit, nodePtr->getLeftPtr(), indentedCount);
		_indentedorder(visit, nodePtr->getRightPtr(), indentedCount);
		indentedCount--;
	}
}

/*
Traverse for display the list in PreOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_preorder(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		nodePtr->getDetail();
		_preorder(nodePtr->getLeftPtr());
		_preorder(nodePtr->getRightPtr());
	}
}

/*
Traverse for display the list in InOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_inorder(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(nodePtr->getLeftPtr());
		nodePtr->getDetail();
		_inorder(nodePtr->getRightPtr());
	}
}  

/*
Traverse for display the list in PostOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_postorder(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(nodePtr->getLeftPtr());
		_postorder(nodePtr->getRightPtr());
		nodePtr->getDetail();
	}
}

/*
'=' Operator
*/

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(BinaryTree<ItemType> & sourceTree)
{
	rootPtr = copyTree(sourceTree.getRootNode());
	return sourceTree;
}

/*
Display the list in stackPreOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::stackPreOrder()
{
	Stack<BinaryNode<ItemType>*> tempstack;
	BinaryNode<ItemType> *newnode;
	newnode = rootPtr;
	tempstack.push(newnode);
	_stackPreOrder(tempstack);
	while (!tempstack.isEmpty())
	{
		tempstack.pop(newnode);
		newnode->getDetail();
	}
}

/*
Display the list in stackInOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::stackInOrder()
{
	Stack<BinaryNode<ItemType>*> tempstack;
	BinaryNode<ItemType> *newnode;
	newnode = rootPtr;
	tempstack.push(newnode);
	_stackInOrder(tempstack);
	while (!tempstack.isEmpty())
	{
		tempstack.pop(newnode);
		newnode->getDetail();
	}
}

/*
Display the list in stackPostOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::stackPostOrder()
{
	Stack<BinaryNode<ItemType>*> tempstack;
	BinaryNode<ItemType> *newnode;
	newnode = rootPtr;
	tempstack.push(newnode);
	_stackPostOrder(tempstack);
	while (!tempstack.isEmpty())
	{
		tempstack.pop(newnode);
		newnode->getDetail();
	}
}

/*
Traverse for display the list in stackPreOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_stackPreOrder(Stack<BinaryNode<ItemType>*> &tempstack)
{
	BinaryNode<ItemType> *newnode;
	tempstack.pop(newnode);
	if (newnode->getRightPtr())
	{
		tempstack.push(newnode->getRightPtr());
		_stackPreOrder(tempstack);
	}
	if (newnode->getLeftPtr())
	{
		tempstack.push(newnode->getLeftPtr());
		_stackPreOrder(tempstack);
	}
	tempstack.push(newnode);
}

/*
Traverse for display the list in stackInOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_stackInOrder(Stack<BinaryNode<ItemType>*> &tempstack)
{
	BinaryNode<ItemType> *newnode;
	tempstack.pop(newnode);
	if (newnode->getRightPtr())
	{
		tempstack.push(newnode->getRightPtr());
		_stackInOrder(tempstack);
	}
	tempstack.push(newnode);
	if (newnode->getLeftPtr())
	{
		tempstack.push(newnode->getLeftPtr());
		_stackInOrder(tempstack);
	}
}

/*
Traverse for display the list in stackPostOrder
*/

template<class ItemType>
void BinaryTree<ItemType>::_stackPostOrder(Stack<BinaryNode<ItemType>*> &tempstack)
{
	BinaryNode<ItemType> *newnode;
	tempstack.pop(newnode);
	tempstack.push(newnode);
	if (newnode->getRightPtr())
	{
		tempstack.push(newnode->getRightPtr());
		_stackPostOrder(tempstack);
	}
	if (newnode->getLeftPtr())
	{
		tempstack.push(newnode->getLeftPtr());
		_stackPostOrder(tempstack);
	}

}

/*
Implemented the longest branch from the binary tree
*/

template<class ItemType>
void BinaryTree<ItemType>::longestBranch()
{
	Stack<BinaryNode<ItemType>*> tempstack;
	BinaryNode<ItemType> *newnode = rootPtr;
	int branchCount = 0;
	int deepestLevel = 0;
	_longestBranch(rootPtr, branchCount, deepestLevel);
	setLongestBranch(rootPtr, deepestLevel, branchCount, tempstack);
	while (tempstack.pop(newnode))
		newnode->getDetail();
}

/*
Traverse for longestBranch
*/

template<class ItemType>
void BinaryTree<ItemType>::_longestBranch(BinaryNode<ItemType>* nodePtr, int branchCount, int & levelCount)
{
	if (nodePtr != 0)
	{
		if (nodePtr->getRightPtr())
		{
			branchCount++;
			if (branchCount > levelCount)
			{
				levelCount++;
			}
			_longestBranch(nodePtr->getRightPtr(), branchCount, levelCount);
			branchCount--;
		}
		if (nodePtr->getLeftPtr())
		{
			branchCount++;
			if (branchCount > levelCount)
			{
				levelCount++;
			}
			_longestBranch(nodePtr->getLeftPtr(), branchCount, levelCount);
			branchCount--;
		}
	}
}

/*
Print out the longest branch from BST to the screen
*/

template<class ItemType>
void BinaryTree<ItemType>::setLongestBranch(BinaryNode<ItemType>* nodePtr, int & levelCount, int branchCount, Stack<BinaryNode<ItemType>*> &tempstack)
{
	if (nodePtr != 0)
	{
		if (nodePtr->getRightPtr())
		{
			branchCount++;
			setLongestBranch(nodePtr->getRightPtr(), levelCount, branchCount, tempstack);
			branchCount--;
		}
		if (nodePtr->getLeftPtr())
		{
			branchCount++;
			setLongestBranch(nodePtr->getLeftPtr(), levelCount, branchCount, tempstack);
			branchCount--;
		}
		if (branchCount == levelCount)
		{
			tempstack.push(nodePtr);
			levelCount--;
		}
	}
}



#endif

//////////////////////////// BinaryTree.h ends here functions ////////////////////////////////////////////
