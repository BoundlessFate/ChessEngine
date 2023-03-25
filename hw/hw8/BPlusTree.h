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
		~BPlusTree();
		void DeleteNode(BPlusTreeNode<T>* node);
		void insert(T key);
		BPlusTreeNode<T>* find(const T& key);
		void print_sideways(std::ofstream& outfile);
		void print_BFS(std::ofstream& outfile);
	private:
		BPlusTreeNode<T>* rootNode;
		int b;
		void insert(T key, BPlusTreeNode<T>* node);
		void split(BPlusTreeNode<T>* node);
		BPlusTreeNode<T>* find(const T key, BPlusTreeNode<T>* node);
		void print_sideways(short depth, BPlusTreeNode<T>* node, std::ofstream& outfile);
		void print_BFS(short depth, short targetDepth, BPlusTreeNode<T>* node, std::ofstream& outfile);
};
template <class T>
BPlusTree<T>::BPlusTree(const int& num) {
	rootNode = NULL;
	b = num;
}
template<class T>
void BPlusTree<T>::insert(T key) {
	if (rootNode == NULL) {
		rootNode = new BPlusTreeNode<T>();
		(*rootNode).keys.push_back(key);
		return;
	}
	insert(key, rootNode);
	return;
}
template <class T>
void BPlusTree<T>::insert(T key, BPlusTreeNode<T>* node) {
	// If you are at the bottom of the branch
	bool inserted = false;
	if ((*node).children.size() == 0) {
		// Insert the key
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			if (key < (*node).keys[i]) {
				(*node).keys.insert((*node).keys.begin()+i, key);
				inserted = true;
			}
		}
		if (!inserted) {
			(*node).keys.push_back(key);
		}
		// If you arent at the bottom node, traverse downward
	} else {
		bool lastIndex = true;
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			if (key < (*node).keys[i]) {
				lastIndex = false;
				insert(key, (*node).children[i]);
				break;
			}
		}
		if (lastIndex)
			insert(key, (*node).children[(*node).keys.size()]);
	}
	// Check for the need to split
	if ((int)(*node).keys.size() >= b)
		split(node);
	return;
}

template <class T>
void BPlusTree<T>::split(BPlusTreeNode<T>* node) {
	if ((*node).parent == NULL) {
		(*node).parent = new BPlusTreeNode<T>;
		rootNode = (*node).parent;
		(*node).parent->children.push_back(node);
	}
	BPlusTreeNode<T>* parentNode = (*node).parent;
	// Get index of currentNode in parent node
	int index = 0;
	T valToCheck = (*node).keys[0];
	for (unsigned int i=0; i<(*parentNode).keys.size(); i++) {
		if (valToCheck > (*parentNode).keys[i])
			index++;
	}
	// Create the new node
	BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>();
	(*newNode).parent = (*node).parent;
	(*parentNode).children.insert((*parentNode).children.begin()+index+1, newNode);
	int tempNum = (int)((*node).keys.size() / 2);
	for (int i=(*node).keys.size() - 1; i>=tempNum; i--) {
		(*newNode).keys.insert((*newNode).keys.begin(), (*node).keys[i]);
		(*newNode).keys.erase((*newNode).keys.begin() + i);
	}
	bool inserted = false;
	T key = (*newNode).keys[0];
	for (unsigned int i=0; i<(*node).keys.size(); i++) {
		if (key < (*node).keys[i]) {
			(*parentNode).keys.insert((*parentNode).keys.begin()+i, key);
			inserted = true;
		}
	}
	if (!inserted)
		(*parentNode).keys.push_back(key);
	// Remove the leftmost key from the newNode if it isnt a child
	if (!(*newNode).is_leaf())
		(*newNode).keys.erase((*newNode).keys.begin());
	// No changes to children if it is a leaf node
	if ((*node).children.size() - 1 < 0)
		return;
	// Edit children for newNode and node
	tempNum = (int)((*node).children.size() / 2);
	for (int i=(*node).children.size() - 1; i>=tempNum; i--) {
		(*newNode).children.insert((*newNode).children.begin(), (*node).children[i]);
		(*newNode).children.erase((*newNode).children.begin() + i);
	}
	return;
}

template <class T>
BPlusTree<T>::~BPlusTree() {
	DeleteNode(rootNode);
	return;
}

template <class T>
void BPlusTree<T>::DeleteNode(BPlusTreeNode<T>* node) {
	for (unsigned int i=0; i<(*node).children.size(); i++) {
		DeleteNode((*node).children[i]);
	}
	(*node).children.clear();
	if ((*node).is_leaf()) {
		delete node;
		return;
	}
	return;
}

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key) {
	if (rootNode == NULL)
		return rootNode;
	return find(key, rootNode);
}
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(T key, BPlusTreeNode<T>* node) {
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

template <class T>
void BPlusTree<T>::print_sideways(std::ofstream& outfile) {
	print_sideways(0, rootNode, outfile);
}
template<class T>
void BPlusTree<T>::print_sideways(short depth, BPlusTreeNode<T>* node, std::ofstream& outfile) {
	if ((*node).is_leaf()) {
		outfile << ('\t' * depth);
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			outfile << (*node).keys[i];
			if (i + 1 <(*node).keys.size())
				outfile << ',';
		}
	} else {
		for (unsigned int i=0; i<((*node).children.size()/2); i++) {
			print_sideways(depth+1, (*node).children[i], outfile);
		}
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			outfile << (*node).keys[i];
			if (i + 1 <(*node).keys.size())
				outfile << ',';
		}
		for (unsigned int i=(int)((*node).children.size()/2); i<(*node).children.size(); i++) {
			print_sideways(depth+1, (*node).children[i], outfile);
		}
	}
	outfile<< std::endl;
	return;
}
template <class T>
void BPlusTree<T>::print_BFS(std::ofstream& outfile) {
	if (rootNode == NULL)
		return;
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
		print_BFS(0, i, rootNode, outfile);
		outfile << std::endl;
	}
}
template <class T>
void BPlusTree<T>::print_BFS(short depth, short targetDepth, BPlusTreeNode<T>* node, std::ofstream& outfile) {
	if (depth == targetDepth) {
		// Print the data for the current node
		for (unsigned int i=0; i<(*node).keys.size(); i++) {
			outfile << (*node).keys[i];
			if (i+1<(*node).keys.size())
				outfile << ',';
		}
		outfile << ' ';
		return;
	}
	for (unsigned int i=0; i<(*node).children.size(); i++) {
		print_BFS(depth + 1, targetDepth, (*node).children[i], outfile);
	}
	return;
}
#endif
