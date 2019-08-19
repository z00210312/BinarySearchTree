// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// Modified by	JIA SHIN TSENG
// Modified day	2/23/2016

//////////////////////////// Main.cpp starts here functions ////////////////////////////////////////////

#include "BinarySearchTree.h"  // BST ADT 
#include <iostream>
#include <string>
#include <fstream>		 // needed for reading the file
#include "Queue.h"

using namespace std;
#define INPUT_FILE "gpa.txt"

/*
Prototypes for main loops, promt, and display
*/
void loadStudents(BinarySearchTree<string>* tree, const char *filename);
void welcomepromt();
void indentedDisplay(string & anItem);
bool maneul(BinarySearchTree<string>* tree);

/*
Main
*/
int main()
{
	BinarySearchTree<string>* tree1Ptr = new BinarySearchTree<string>();

	loadStudents(tree1Ptr, INPUT_FILE);
	if(maneul(tree1Ptr))

	delete tree1Ptr;
	return 0;
}  

/*
Read the strings from the text file
*/
void loadStudents(BinarySearchTree<string> *tree, const char *filename)
{
	ifstream inputFile;
	inputFile.open(filename);
	string studentID;
	string name;
	float gpa;
	while (!inputFile.eof())
	{
		getline(inputFile, studentID, ' ');
		getline(inputFile, name, ';'); 
		inputFile >> gpa;
		tree->insert(studentID, name, gpa);
		getline(inputFile, studentID, '\n');
	}
}

/*
Display the meneul promt
*/
void welcomepromt()
{
	cout << "T - Print tree as an indented list(show level numbers)" << endl;
	cout << "S - Search by a unique key (student ID)" << endl;
	cout << "B - Tree Breadth-First Traversal: Print by level" << endl;
	cout << "D - Depth - First Traversals : inorder, preorder, postorder" << endl;
	cout << "I - Iterative Depth - First Traversals : inorder, preorder, postorder" << endl;
	cout << "R - Find the longest branch and print it (from leaf to root)" << endl; 
	cout << "H - Help - to show the menu" << endl;
	cout << "Q - Quit" << endl;
}

/*
Display an single item in the node
*/
void indentedDisplay(string & anItem)
{
	cout << anItem << endl;
}

/*
Loops main
*/
bool maneul(BinarySearchTree<string>* tree)
{
	cout << "Type 'H' for the help" << endl;
	char loopkey = 0;
	while (!(loopkey == 'q' || loopkey == 'Q'))
	{
		cout << "Input : ";
		cin >> loopkey;
		if (loopkey == 't' || loopkey == 'T')
		{
			tree->indentedOrder(indentedDisplay);
		}
		else if (loopkey == 's' || loopkey == 'S')
		{
			string returnedString;
			cout << "Enter the ID : ";
			cin >> returnedString;
			cout << "Searching for the ID : " << returnedString << endl;;
			if(!tree->getEntry(returnedString))
				cout << "Entry not in tree." << endl;
		}
		else if (loopkey == 'b' || loopkey == 'B')
		{
			Queue<BinaryNode<string>*> tempqueue;
			BinaryNode<string> *newnode;
			newnode = tree->getRootNode();
			tempqueue.enqueue(newnode);
			while (!tempqueue.isEmpty())
			{
				tempqueue.dequeue(newnode);
				if (newnode->getLeftPtr())
					tempqueue.enqueue(newnode->getLeftPtr());
				if (newnode->getRightPtr())
					tempqueue.enqueue(newnode->getRightPtr());
				newnode->getDetail();
			}
		}
		else if (loopkey == 'd' || loopkey == 'D')
		{
			cout << "1. PreOrder\n2. InOrder\n3. PostOrder\n";
			cin >> loopkey;
			if (loopkey == '1')
				tree->preOrder();
			else if (loopkey == '2')
				tree->inOrder();
			else if (loopkey == '3')
				tree->postOrder();
			else
				cout << "wrong choice!" << endl;
		}
		else if (loopkey == 'i' || loopkey == 'I')
		{
			cout << "1. PreOrder\n2. InOrder\n3. PostOrder\n";
			cin >> loopkey;
			if (loopkey == '1')
				tree->stackPreOrder();
			else if (loopkey == '2')
				tree->stackInOrder();
			else if (loopkey == '3')
				tree->stackPostOrder();
			else
				cout << "wrong choice!" << endl;
		}
		else if (loopkey == 'r' || loopkey == 'R')
		{
			cout << "THe longest branch from leaf to root is : " << endl;
			tree->longestBranch();
		}
		else if (loopkey == 'h' || loopkey == 'H')
		{
			welcomepromt();
		}
	}
	return true;
}

/*
Type 'H' for the help
h
T - Print tree as an indented list(show level numbers)
S - Search by a unique key (student ID)
B - Tree Breadth-First Traversal: Print by level
D - Depth - First Traversals : inorder, preorder, postorder
I - Iterative Depth - First Traversals : inorder, preorder, postorder
R - Find the longest branch and print it (from leaf to root)
H - Help - to show the menu
Q - Quit
Input : t
1. 3800
	2. 3000
		3. 1900
			4. 1500
			4. 2100
				5. 2800
					6. 2500
		3. 3500
			4. 3300
	2. 4300
		3. 3900
			4. 4200
		3. 5000
Input : s
Enter the ID : 230
Searching for the ID : 230
Entry not in tree.
Input : s
Enter the ID : 5000
Searching for the ID : 5000
5000 Lee, Lucy Marie, GPA: 3.4
Input : b
3800 Lee, Victor              2.8
3000 Brown, Joanne            4.0
4300 Trapp, Amanda Elizabeth  4.0
1900 Walljasper, Bryan        3.9
3500 Marcus, John             3.2
3900 Brown, Joanne            3.5
5000 Lee, Lucy Marie          3.4
1500 Marcus, John             4.0
2100 Andrews, Dennis          2.9
3300 Lee, Victor              3.6
4200 Brown, Joanne            4.0
2800 Brown, Joanne            2.6
2500 Lee, Mary                3.8
Input : d
1. PreOrder
2. InOrder
3. PostOrder
1
3800 Lee, Victor              2.8
3000 Brown, Joanne            4.0
1900 Walljasper, Bryan        3.9
1500 Marcus, John             4.0
2100 Andrews, Dennis          2.9
2800 Brown, Joanne            2.6
2500 Lee, Mary                3.8
3500 Marcus, John             3.2
3300 Lee, Victor              3.6
4300 Trapp, Amanda Elizabeth  4.0
3900 Brown, Joanne            3.5
4200 Brown, Joanne            4.0
5000 Lee, Lucy Marie          3.4
Input : d
1. PreOrder
2. InOrder
3. PostOrder
2
1500 Marcus, John             4.0
1900 Walljasper, Bryan        3.9
2100 Andrews, Dennis          2.9
2500 Lee, Mary                3.8
2800 Brown, Joanne            2.6
3000 Brown, Joanne            4.0
3300 Lee, Victor              3.6
3500 Marcus, John             3.2
3800 Lee, Victor              2.8
3900 Brown, Joanne            3.5
4200 Brown, Joanne            4.0
4300 Trapp, Amanda Elizabeth  4.0
5000 Lee, Lucy Marie          3.4
Input : d
1. PreOrder
2. InOrder
3. PostOrder
3
1500 Marcus, John             4.0
2500 Lee, Mary                3.8
2800 Brown, Joanne            2.6
2100 Andrews, Dennis          2.9
1900 Walljasper, Bryan        3.9
3300 Lee, Victor              3.6
3500 Marcus, John             3.2
3000 Brown, Joanne            4.0
4200 Brown, Joanne            4.0
3900 Brown, Joanne            3.5
5000 Lee, Lucy Marie          3.4
4300 Trapp, Amanda Elizabeth  4.0
3800 Lee, Victor              2.8
Input : i
1. PreOrder
2. InOrder
3. PostOrder
1
3800 Lee, Victor              2.8
3000 Brown, Joanne            4.0
1900 Walljasper, Bryan        3.9
1500 Marcus, John             4.0
2100 Andrews, Dennis          2.9
2800 Brown, Joanne            2.6
2500 Lee, Mary                3.8
3500 Marcus, John             3.2
3300 Lee, Victor              3.6
4300 Trapp, Amanda Elizabeth  4.0
3900 Brown, Joanne            3.5
4200 Brown, Joanne            4.0
5000 Lee, Lucy Marie          3.4
Input : i
1. PreOrder
2. InOrder
3. PostOrder
2
1500 Marcus, John             4.0
1900 Walljasper, Bryan        3.9
2100 Andrews, Dennis          2.9
2500 Lee, Mary                3.8
2800 Brown, Joanne            2.6
3000 Brown, Joanne            4.0
3300 Lee, Victor              3.6
3500 Marcus, John             3.2
3800 Lee, Victor              2.8
3900 Brown, Joanne            3.5
4200 Brown, Joanne            4.0
4300 Trapp, Amanda Elizabeth  4.0
5000 Lee, Lucy Marie          3.4
Input : i
1. PreOrder
2. InOrder
3. PostOrder
3
1500 Marcus, John             4.0
2500 Lee, Mary                3.8
2800 Brown, Joanne            2.6
2100 Andrews, Dennis          2.9
1900 Walljasper, Bryan        3.9
3300 Lee, Victor              3.6
3500 Marcus, John             3.2
3000 Brown, Joanne            4.0
4200 Brown, Joanne            4.0
3900 Brown, Joanne            3.5
5000 Lee, Lucy Marie          3.4
4300 Trapp, Amanda Elizabeth  4.0
3800 Lee, Victor              2.8
Input : r
THe longest branch from leaf to root is : 
2500 Lee, Mary                3.8
2800 Brown, Joanne            2.6
2100 Andrews, Dennis          2.9
1900 Walljasper, Bryan        3.9
3000 Brown, Joanne            4.0
3800 Lee, Victor              2.8
Input : q

*/

//////////////////////////// Main.cpp ends here functions ////////////////////////////////////////////