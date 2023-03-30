/* ASSUMPTIONS:
   1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
   2. There will never be a duplicate key passed to insert.
   */

#include <vector>
#include <fstream>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
	public:
		BPlusTreeNode() : parent(NULL) {};
		bool is_leaf();
		bool contains(const T& key);

		//For grading only. This is bad practice to have, because
		//it exposes a private member variable.
		BPlusTreeNode* get_parent() { return parent; } 

		//We need this to let BPlusTree access private members
		friend class BPlusTree<T>; 
	private:
		bool contains(const T& key,std::size_t low,std::size_t high);
		std::vector<T> keys;
		std::vector<BPlusTreeNode*> children;
		BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree{
	public:
		BPlusTree(const int& num);
		BPlusTree(BPlusTree& a);
		~BPlusTree();
		void CopyHelper(BPlusTreeNode<T>* node);
		void DeleteNode(BPlusTreeNode<T>* node);
		void insert(T key);
		BPlusTreeNode<T>* find(const T& key);
		void print_sideways(std::ofstream& outfile);
		void print_BFS(std::ofstream& outfile);
		// Returns b
		int GetB() {return b;}
		// Returns the root node
		BPlusTreeNode<T>* GetRootNode() {return rootNode;}
	private:
		BPlusTreeNode<T>* rootNode;
		int b;
		void insert(T key, BPlusTreeNode<T>* node);
		void split(BPlusTreeNode<T>* node);
		BPlusTreeNode<T>* find(const T key, BPlusTreeNode<T>* node);
		void print_sideways(short depth, BPlusTreeNode<T>* node, std::ofstream& outfile);
		void print_BFS(short depth, short int targetDepth,
				BPlusTreeNode<T>* node, std::ofstream& outfile, bool& firstOnLine);
};
// Main constructor
template <class T>
BPlusTree<T>::BPlusTree(const int& num) {
	rootNode = NULL;
	// Set the b value
	b = num;
	return;
}
// Copy Constructor
template <class T>
BPlusTree<T>::BPlusTree(BPlusTree& a) {
	rootNode = NULL;
	// Set the b value from the other tree
	b = a.GetB();
	CopyHelper(a.GetRootNode());
	return;
}
// Helper function for the copy constructor
template <class T>
void BPlusTree<T>::CopyHelper(BPlusTreeNode<T>* node) {
	// Insert the keys if they are a leaf node
	if ((*node).is_leaf()) {
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			insert((*node).keys[i]);
		}
		return;
	}
	// Go down a level
	for (unsigned int i=0; i<(*node).children.size(); i++) {
		CopyHelper((*node).children[i]);
	}
	return;
}
// Insert key into nodes
template<class T>
void BPlusTree<T>::insert(T key) {
	// If the tree is empty, add key to a new root node
	if (rootNode == NULL) {
		rootNode = new BPlusTreeNode<T>();
		(*rootNode).keys.push_back(key);
		return;
	}
	// Call the recursive helper function
	insert(key, rootNode);
	return;
}
// Helper function for insert
template <class T>
void BPlusTree<T>::insert(T key, BPlusTreeNode<T>* node) {
	// If you are at the bottom of the branch
	bool inserted = false;
	if ((*node).is_leaf()) {
		// Insert the key
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			if (key < (*node).keys[i]) {
				(*node).keys.insert((*node).keys.begin()+i, key);
				inserted = true;
				break;
			}
		}
		// Insert it at the end of the key vector if it is the greatest value
		if (!inserted) {
			(*node).keys.push_back(key);
		}
		// If you arent at the bottom node, traverse downward
	} else {
		// Recurse to the proper child
		bool lastIndex = true;
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			if (key < (*node).keys[i]) {
				lastIndex = false;
				insert(key, (*node).children[i]);
				break;
			}
		}
		// Recurse to the last child if it not in
		if (lastIndex)
			insert(key, (*node).children[(*node).keys.size()]);
	}
	// Check for the need to split
	if ((int)(*node).keys.size() >= b)
		split(node);
	return;
}
// Split if the number of children is greater than b
template <class T>
void BPlusTree<T>::split(BPlusTreeNode<T>* node) {
	// If the root node needed to be split
	if ((*node).parent == NULL) {
		// Create a new parent node
		(*node).parent = new BPlusTreeNode<T>;
		// Set up the parenting and children settings
		rootNode = (*node).parent;
		(*node).parent->children.push_back(node);
	}
	// Get a reference to parentNode for ease of use
	BPlusTreeNode<T>* parentNode = (*node).parent;
	// Get index of currentNode in parent node
	int index = 0;
	T valToCheck = (*node).keys[0];
	for (unsigned int i=0; i<(*parentNode).keys.size(); i++) {
		if (valToCheck >= (*parentNode).keys[i])
			index++;
	}
	// Create the new node
	BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>();
	// Set its parent to the same parent as the current node
	(*newNode).parent = parentNode;
	// Add this new node 1 spot after the old one in the parents children vector
	(*parentNode).children.insert((*parentNode).children.begin()+index+1, newNode);
	// current node keys / 2
	int tempNum = (int)((*node).keys.size() / 2);
	// Iterate backwards through the current nodes keys
	for (int i=(*node).keys.size() - 1; i>=tempNum; i--) {
		// Add said key to the new node
		(*newNode).keys.insert((*newNode).keys.begin(), (*node).keys[i]);
		// Erase said key from the old node
		(*node).keys.erase((*node).keys.begin() + i);
	}
	bool inserted = false;
	T key = (*newNode).keys[0];
	// Insert the first key on the new node to the parent
	for (unsigned int i=0; i<(*parentNode).keys.size(); i++) {
		if (key < (*parentNode).keys[i]) {
			(*parentNode).keys.insert((*parentNode).keys.begin()+i, key);
			inserted = true;
			break;
		}
	}
	if (!inserted)
		(*parentNode).keys.push_back(key);
	// Repeat the same process with the keys with the children
	if ((*node).children.size() > 0) {
		tempNum = (int)((*node).children.size() / 2);
		for (int i=(*node).children.size() - 1; i>=tempNum; i--) {
			(*newNode).children.insert((*newNode).children.begin(), (*node).children[i]);
			(*(*newNode).children[0]).parent = newNode;
			(*node).children.erase((*node).children.begin() + i);
		}
	}
	// Remove the leftmost key from the newNode if it isnt a child
	if (!(*newNode).is_leaf()) {
		(*newNode).keys.erase((*newNode).keys.begin());
	}
	return;
}
// Deconstructor
template <class T>
BPlusTree<T>::~BPlusTree() {
	// Dont do anything with an empty tree
	if (rootNode == NULL)
		return;
	// Call helper function
	DeleteNode(rootNode);
	return;
}
// Recursive helper for the deconstructor
template <class T>
void BPlusTree<T>::DeleteNode(BPlusTreeNode<T>* node) {
	// Loops through and recurses to the children
	for (unsigned int i=0; i<(*node).children.size(); i++) {
		DeleteNode((*node).children[i]);
	}
	// Clear the children out of the vector
	(*node).children.clear();
	// If it is a leaf node
	if ((*node).is_leaf()) {
		// Delete the node
		delete node;
		return;
	}
	return;
}
// Find function to find the node with the requested key
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key) {
	// return null if it is a empty tree
	if (rootNode == NULL)
		return NULL;
	// Call the recursive helper function
	return find(key, rootNode);
}
// Recursive function for find
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(T key, BPlusTreeNode<T>* node) {
	// Return the node if it is a leaf
	if ((*node).is_leaf())
		return node;
	// If it is not a leaf, recurse further down
	for (unsigned int i=0; i<(*node).keys.size(); i++) {
		if (key < (*node).keys[i]) {
			return find(key, (*node).children[i]);
		}
	}
	return find(key, (*node).children[(*node).keys.size()]);
}
// Print sideways function to an outfile
template <class T>
void BPlusTree<T>::print_sideways(std::ofstream& outfile) {
	// Dont recurse if it is empty 
	if (rootNode == NULL) {
		outfile << "Tree is empty." << std::endl;
		return;
	}
	// Call the recursive helper function
	print_sideways(0, rootNode, outfile);
}
// Recursive helper function for print sideways
template<class T>
void BPlusTree<T>::print_sideways(short depth, BPlusTreeNode<T>* node, std::ofstream& outfile) {
	// Print out the keys if it is a leaf
	if ((*node).is_leaf()) {
		for (unsigned int i=0; i<(uint)depth; i++)
			outfile << '\t';
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			outfile << (*node).keys[i];
			if (i + 1 <(*node).keys.size())
				outfile << ',';
		}
	// If it isnt a leaf
	} else {
		// Recurse through the first half of the children
		for (unsigned int i=0; i<((*node).children.size()/2); i++) {
			print_sideways(depth+1, (*node).children[i], outfile);
		}
		// Print the current node
		for (unsigned int i=0; i<(uint)depth; i++)
			outfile << '\t';
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			outfile << (*node).keys[i];
			if (i + 1 <(*node).keys.size())
				outfile << ',';
		}
		outfile << std::endl;
		// Recurse through the rest of the children
		for (unsigned int i=(int)((*node).children.size()/2); i<(*node).children.size(); i++) {
			print_sideways(depth+1, (*node).children[i], outfile);
		}
		return;
	}
	outfile<< std::endl;
	return;
}
// Other print function (Breadth First Search)
template <class T>
void BPlusTree<T>::print_BFS(std::ofstream& outfile) {
	// Dont recurse if it is an empty tree
	if (rootNode == NULL) {
		outfile << "Tree is empty." << std::endl;
		return;
	}
	// Find the max depth
	short maxDepth = 0;
	BPlusTreeNode<T>* currentNode = rootNode;
	while (true) {
		if ((*currentNode).is_leaf())
			break;
		currentNode = (*currentNode).children[0];
		maxDepth += 1;
	}
	// Iterate through all levels of the tree
	for (short i=0; i<=maxDepth; i++) {
		bool firstOnLine = true;
		// Recursive helper function
		print_BFS(0, i, rootNode, outfile, firstOnLine);
		outfile << std::endl;
	}
}
// Recursive helper function for print BFS
template <class T>
void BPlusTree<T>::print_BFS(short depth, short targetDepth, BPlusTreeNode<T>* node, std::ofstream& outfile, bool& firstOnLine) {
	// Print out the current keys if it is on the right depth
	if (depth == targetDepth) {
		if (!firstOnLine) {
			outfile << '\t';
		}
		// Print the data for the current node
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			outfile << (*node).keys[i];
			if (i+1<(*node).keys.size())
				outfile << ',';
		}
		firstOnLine = false;
		return;
	}
	// If it isnt on the right depth, do down a level in depth and add 1 to depth
	for (unsigned int i=0; i<(*node).children.size(); i++) {
		print_BFS(depth + 1, targetDepth, (*node).children[i], outfile, firstOnLine);
	}
	return;
}
#endif
