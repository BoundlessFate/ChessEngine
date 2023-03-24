/* ASSUMPTIONS:
   1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
   2. There will never be a duplicate key passed to insert.
   */

#include <vector>

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
		void insert(const T& key);
	private:
		T rootNode;
		int b;
		void insert(const T& key, BPlusTreeNode<T>& node);
		void split(BPlusTreeNode<T>& node);
};
template <class T>
BPlusTree<T>::BPlusTree(const int& num) {
	rootNode = NULL;
	b = num;
}
template<class T>
void BPlusTree<T>::insert(const T& key) {
	if (rootNode == NULL) {
		rootNode = new BPlusTreeNode<T>();
		rootNode.keys.push_back(key);
		return;
	}
	insert(key, rootNode);
	return;
}
template <class T>
void BPlusTree<T>::insert(const T& key, BPlusTreeNode<T>& node) {
	// If you are at the bottom of the branch
	bool inserted = false;
	if (node.children.size() == 0) {
		// Insert the key
		for (unsigned int i=0; i<node.keys.size(); i++) {
			if (key < node.keys[i]) {
				node.keys.insert(key, i);
				inserted = true;
			}
		}
		if (!inserted) {
			node.keys.push_back(key);
		}
		// If you arent at the bottom node, traverse downward
	} else {
		bool lastIndex = true;
		for (unsigned int i=0; i<node.keys.size(); i++) {
			if (key < node.keys[i]) {
				lastIndex = false;
				if (insert(key, node.children[i]))
					split(node, i);
				break;
			}
		}
		if (lastIndex) {
			if (insert(key, node.children[node.keys.size()]))
				split(node, node.keys.size());
		}
	}
	// Check for the need to split
	if (node.key.size() >= b)
		split(node);
	return;
}

template <class T>
void BPlusTree<T>::split(BPlusTreeNode<T>& node) {
	if (node.parent == NULL) {
		node.parent = new BPlusTreeNode<T>;
		node.parent.children.push_back(node);
	}
	BPlusTreeNode<T> parentNode = node.parent;
	// Get index of currentNode in parent node
	int index = 0;
	T valToCheck = node.keys();
	for (unsigned int i=0; i<parentNode.keys.size(); i++) {
		if (valToCheck > parentNode.keys[i])
			index++;
	}
	// Create the new node
	BPlusTreeNode<T> newNode = new BPlusTreeNode<T>();
	newNode.parent = node.parent;
	parentNode.children.insert(newNode, index + 1);
	int tempNum = (int)(node.keys.size() / 2);
	for (unsigned int i=node.keys.size() - 1; i>=tempNum; i--) {
		newNode.keys.push_front(node.keys[i]);
		newNode.keys.remove(i);
	}
	bool inserted = false;
	T key = newNode.keys[0];
	for (unsigned int i=0; i<node.keys.size(); i++) {
		if (key < node.keys[i]) {
			parentNode.keys.insert(key, i);
			inserted = true;
		}
	}
	if (!inserted)
		parentNode.keys.push_back(key);
	// Remove the leftmost key from the newNode if it isnt a child
	if (!newNode.is_leaf())
		newNode.keys.pop_front();
	// No changes to children if it is a leaf node
	if (node.children.size() - 1 < 0)
		return;
	// Edit children for newNode and node
	tempNum = (int)(node.children.size() / 2);
	for (unsigned int i=node.children.size() - 1; i>=tempNum; i--) {
		newNode.children.push_front(node.children[i]);
		newNode.children.remove(i);
	}
	return;
}

#endif
