#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

struct BST::Node
{
	// Member variables
	KeyType key;
	ItemType item;
	Node* leftChild;
	Node* rightChild;
	Node* parent;

	// Node constructor
	Node() : leftChild(0), rightChild(0), parent(0) {};

	// Node constructor for initialize data members
	Node(KeyType key, ItemType item) : key(key), item(item) {};

	// Node constructor for initialize soughtKey
	Node(KeyType soughtKey) : key(soughtKey) {};
};

// Calling function insert(KeyType, ItemType)
void BST::insert(KeyType key, ItemType item)
{
	// tempNode here is the inserting node
	Node* tempNode = new Node(key, item);
	Node* parentNode = nullptr;
	Node* childNode = nullptr;
	tempNode->key = key;
	tempNode->item = item;

	root = childNode;

	while (childNode != nullptr)
	{
		// the parent node goes to the place of findpath node
		// identify whether the path is going to left side or right side
		parentNode = childNode;
		if (tempNode->key < childNode->key)
		{ 
			childNode = childNode->leftChild;
		}
		else 
		{
			childNode = childNode->rightChild;
		}
	}

	// parentNode becomes the parent of the tempNode
	// let tempNode's parent pointer leads to parentNode
	// connect the tree with tempNode
	tempNode->parent = parentNode;

	if (parentNode == nullptr)
	{
		this->root = tempNode;
	}
	else if (tempNode->key < parentNode->key)
	{
		parentNode->leftChild = tempNode;
	}
	else
	{
		parentNode->rightChild = tempNode;
	}
}

// recursive insert() function [ADVANCED TASK]
void BST::insertRec(KeyType k, ItemType i, Node* & current)
{
	// tempNode here is the inserting node
	Node* tempNode = new Node(k, i);
	Node* parentNode = nullptr;
	Node* childNode = nullptr;
	tempNode->key = k;
	tempNode->item = i;
	tempNode = current;

	// if the tempNode is a leaf, return to the recursive insert function
	// else, recursion starts
	if (isLeaf(current))
	{
		return insertRec(k, i, current);
	}
	else
	{
		// the parent node goes to the place of findpath node
		// identify whether the recursive is going to left side or right side
		parentNode = childNode;
		if (tempNode->key < childNode->key)
		{
			insertRec(k, i, current->leftChild);
		}
		else
		{
			insertRec(k, i, current->rightChild);
		}
		// parentNode becomes the parent of the tempNode
		// let tempNode's parent pointer leads to parentNode
		// connect the tree with tempNode
		if (parentNode == nullptr)
		{
			this->root = tempNode;
		}
		else if (tempNode->key < parentNode->key)
		{
			k, i, current->leftChild = tempNode;
		}
		else
		{
			k, i, current->rightChild = tempNode;
		}
	}
	return;
}

// Calling function remove(KeyType) [ADVANCED TASK]
void BST::remove(KeyType key)
{
	Node* parentNode = nullptr;
	Node* childNode = nullptr;

	// find if there are any key node exist
	// tempNode here is the removing node
	Node* tempNode = find(key);

	// if there is no key node found
	if (tempNode == nullptr) 
	{
		cout << "Cannot find anything." << endl;
		return;
	}

	if (tempNode->leftChild == nullptr || tempNode->rightChild == nullptr) 
	{
		parentNode = tempNode;
	}
	else 
	{
		// let parentNode be tempNode's successor
		parentNode = Successor(tempNode);
	}

	// if the value is not null, let childNode be parentNode's leftchild
	// else, let childNode be parentNode's rightchild
	if (parentNode->leftChild != nullptr) 
	{
		
		childNode = parentNode->leftChild;
	}
	else 
	{
		childNode = parentNode->rightChild;
	}

	if (childNode != nullptr)
	{
		// put childNode back to the tree before parentNode is removed
		childNode->parent = parentNode->parent;
	}

	// let the removing node's parent point to the new childNode, if the parentNode's parent value is null
	// replace parentNode with the childNode where the leftChild is, if the parentNode was the leftChild of its parent
	// replace parentNode with the childNode where the rightChild is, if the parentNode was the rightChild of its parent
	if (parentNode->parent == nullptr)
	{
		this->root = childNode;
	}
	else if (parentNode == parentNode->parent->leftChild)
	{
		parentNode->parent->leftChild = childNode;
	}
	else 
	{
		parentNode->parent->rightChild = childNode;
	}
	
	// replace tempNode's value with parentNode's value
	if (parentNode != tempNode)
	{
		tempNode->key = parentNode->key;
	}

	// remove the parentNode
	delete parentNode;
}

// iteration lookup() function
BST::ItemType * BST::lookup(KeyType soughtKey)
{
	// let current as pointer to root as the start point of the traversal
	Node* current = root;

	while (current != nullptr && soughtKey != current->key)
	{
		if (soughtKey < current->key)
		{
			// to left side
			current = current->leftChild;
		}
		else
		{
			// to right side
			current = current->rightChild;
		}
	}
	return false;
}

// recursive lookup() function
BST::ItemType* BST::lookupRec(KeyType soughtKey, Node* currentNode)
{
	// base case
	if (isLeaf(currentNode))
	{
		return false;
	}

	// recursion starts
	else
	{
		if (soughtKey == currentNode->key)
		{
			return lookupRec(soughtKey, currentNode);
		}
		else if (soughtKey > currentNode->key)
		{
			return lookupRec(soughtKey, currentNode->leftChild);
		}
		else
		{
			return lookupRec(soughtKey, currentNode->rightChild);
		}
	}
}

// display node function
void BST::displayEntries()
{
	Node* current = new Node;
	current = Leftmost(root);
	while (current)
	{
		cout << "(" << current->key << ", " << current->item << ")" << " ";
		current = Successor(current);
	}
}

// destructor
BST::~BST()
{
	deepDelete(root);
}

// destructor for deep deleting the whole tree
void BST::deepDelete(Node* current)
{
	// base case
	if (current != nullptr)
	{
		return;
	}
	// delete all tree nodes
	deepDelete(current->leftChild);
	deepDelete(current->rightChild);

	cout << "Deep deleting all nodes... " << current->key, current->item;
	delete current;
}

BST::Node * BST::Leftmost(Node * current)
{
	while (current->leftChild != nullptr) 
	{
		current = current->leftChild;
	}
	return current;
}

BST::Node * BST::Successor(Node * current)
{
	Node* tempNode = current->parent;

	if (current->rightChild != nullptr) 
	{
		return Leftmost(current->rightChild);
	}

	while (tempNode != nullptr && current == tempNode->rightChild)
	{
		current = tempNode;
		tempNode = tempNode->parent;
	}

	return tempNode;
}

BST::Node* BST::leaf()
{
	return nullptr;
}

bool BST::isLeaf(Node* n)
{
	return (n == nullptr);
}

BST::Node * BST::find(KeyType key)
{
	return nullptr;
}

int main()
{
	BST tree;
	tree.insert(2, "hello");
	tree.insert(100, "bye");
	tree.insert(1, "hi");
	tree.insert(61, "wow");
	cout << "Displays the dictionary entries in key order:" << endl;
	tree.displayEntries();
	cout << endl << endl;

	return 0;
}
