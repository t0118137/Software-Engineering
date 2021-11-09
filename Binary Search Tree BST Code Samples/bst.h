#include <string>

class BST
{
public:
	using KeyType = int;
	using ItemType = std::string;
	ItemType* lookup(KeyType); // return pointer to the item
	void insert(KeyType, ItemType); // insertion
	void remove(KeyType); // removal
	void displayEntries(); // display tree

	BST() = default; // generate the empty constructor
	~BST(); // destructor
private:
	struct Node;
	Node* root; // pointer to the root node
	Node* Leftmost(Node *current);
	Node* Successor(Node *current);

	static Node* leaf();
	static bool isLeaf(Node*);

	Node* find(KeyType key);
	ItemType* lookupRec(KeyType, Node*);
	void insertRec(KeyType, ItemType, Node* &);

	void deepDelete(Node*);
};
