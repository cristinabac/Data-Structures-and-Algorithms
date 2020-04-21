#include "SortedBag.h"
#include "SortedBagIterator.h"

//O(n), where n is the number of unique elems
Node * SortedBag::getMinimum(Node* start)
{
	Node *currentNode = start;
	Node *minNode = start;

	while (currentNode != nullptr) {
		minNode = currentNode;
		currentNode = currentNode->left;
	}
	return minNode;
}

//O(n), where n is the number of unique elems
Node * SortedBag::getMaximum(Node* start)
{
	Node *currentNode = start;
	Node *maxNode = start;

	while (currentNode != nullptr) {
		maxNode = currentNode;
		currentNode = currentNode->right;
	}
	return maxNode;
}


//theta(1)
SortedBag::SortedBag(Relation r)
{
	this->r = r;
	this->root = nullptr;
	this->nrElems = 0;
}


//theta(1)
bool SortedBag::isEmpty() const
{
	return (this->nrElems == 0);
}

int SortedBag::my_function(Node * node, int f) const
{
	if (node != nullptr)
	{
		if (node->frequency == f)
			return 1 + this->my_function(node->left, f) + this->my_function(node->right, f);
		else
			return this->my_function(node->left, f) + this->my_function(node->right, f);
	}
	return 0; //we reached an end

}
//theta(nr of unique keys) - bc we parse once all elements
int SortedBag::elementsWithThisFrequency(int freq) const
{
	return this->my_function(this->root, freq);
}



//O(h) => O(n), where n is the number of unique elems
//from the while loop, just like in case of search
void SortedBag::add(TComp e)
{
	Node *currentNode = this->root;
	Node* parent = nullptr; //for the case we do not have the element in the bag, we will need to know its parent in order to put it as a new node

	while (currentNode != nullptr) {
		parent = currentNode;
		if (currentNode->value == e) {
			currentNode->frequency++; //the element already exists, so just increase its frequency :)
			this->nrElems++;
			return;
		}
		else if (this->r(e, currentNode->value)) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}

	//the element is not in the bag
	//so we need to make a new node 
	Node* newNode = new Node;
	newNode->value = e;
	newNode->frequency = 1; //bc we will put it now for the first tme, so the freq is 1
	newNode->left = nullptr;
	newNode->right = nullptr;

	//but where we put this node?
	//in the loop we made at the beginning, we stored in the -parent- node the node that should be the parent of this new node
	//we use the parent just in case that the element does not already exist in the bag
	if (this->root == nullptr) { //the bag is empty => the new node will be the root
		this->root = newNode;
	}
	else if (this->r(e, parent->value)) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}
	this->nrElems++;
}


Node * SortedBag::removeRec(Node * node, TComp e, bool & removed)
{
	if (node == nullptr) {
		return node;
	}

	if (e == node->value) { //we found the element we want to remove
		removed = true;		//we set the removed bool in order to know in the remove fct if the operation was successfull
		node->frequency--;
		if (node->frequency == 0)
		{	
			//we have to delete the node
			if (node->left == nullptr) {	//we have no left child, so in place of my node will be his right child
				Node* rightSon = node->right;
				delete node;
				return rightSon;
			}
			else if (node->right == nullptr) {
				Node* leftSon = node->left;
				delete node;
				return leftSon;
			}
			else {		//we have both right and left child
				Node *maxNode = this->getMaximum(node->left);  //in place of my node will be the maximum element from the left subtree
				node->value = maxNode->value;
				node->frequency = maxNode->frequency;
				node->left = this->removeRec(node->left, maxNode->value, removed);
			}
		}
		else
			return node; //the freq was not 0, so we do not have to delete the node, jut return it
	}
	else if (this->r(e, node->value)) {
		node->left=this->removeRec(node->left, e, removed);
	}
	else {
		node->right = this->removeRec(node->right, e, removed);
	}
	return node;
}



//O(n), where n is the number of unique elems
bool SortedBag::remove(TComp e)
{
	bool removed = false;
	this->root = this->removeRec(this->root, e, removed);
	if (removed)
		this->nrElems--;
	return removed;
}


//O(h) => O(n), where n is the number of unique elems
//bc if the tree is degenerated, the height is n
bool SortedBag::search(TComp e) const
{
	Node *currentNode = this->root;

	while (currentNode != nullptr) {
		if (currentNode->value == e) {
			return true;
		}
		else if (this->r(e, currentNode->value)) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
	return false;
}

////O(h) => O(n), where n is the number of unique elems
//like at the search function
int SortedBag::nrOccurrences(TComp e) const
{
	Node *currentNode = this->root;

	while (currentNode != nullptr) {
		if (currentNode->value == e) {
			return currentNode->frequency;
		}
		else if (this->r(e, currentNode->value)) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
	return 0; //the element is not in the bag
}


//theta(1)
int SortedBag::size() const
{
	return this->nrElems;
}


//theta(1)
SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}














































SortedBag::~SortedBag()
{
}