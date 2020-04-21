#include "SortedBagIterator.h"


//Inorder traversal
//We start with an empty stack and a current node set to the root
//While current node is not NIL, push it to the stack and set it to its left child
//While stack not empty
//Pop a node and visit it
//Set current node to the right child of the popped node
///While current node is not NIL, push it to the stack and set it to its left child
//Time complexity theta(n), extra space complexity O(n)



//O(n), where n is the number of unique elements
SortedBagIterator::SortedBagIterator(const SortedBag& c):
	c{c}, stack{std::stack<Node*>{}}
{
	this->first();
}

//we go left as far as we can
//so here we reach the most left leaf
//so, the complexity is O(h) => O(n)
void SortedBagIterator::first()
{
	stack = std::stack<Node*>{};

	this->currentNode = this->c.root;
	this->freq_ind = 1;
	while (this->currentNode != nullptr)
	{
		//go left as far as we can
		stack.push(this->currentNode);
		this->currentNode = this->currentNode->left;
	}
	if (stack.empty() == false) {
		this->currentNode = stack.top();
	}
	else {
		currentNode = nullptr;
	}
}

//O(n)
void SortedBagIterator::next()
{
	
	if (!valid())
		throw std::exception();

	if (this->freq_ind < this->currentNode->frequency)
	{
		//we are on the same element
		//just increase the frequency
		this->freq_ind++;
	}
	else
	{
		Node* node = this->stack.top();
		this->stack.pop();

		if (node->right != nullptr) {
			node = node->right;
			while (node != nullptr) {
				this->stack.push(node);
				node = node->left;
			}
		}

		if (this->stack.empty() == false) {
			this->currentNode = this->stack.top();
			this->freq_ind = 1;
		}
		else {
			this->currentNode = nullptr;
		}
	}
}


//theta(1)
bool SortedBagIterator::valid() const
{
	return this->currentNode != nullptr;
}


//theta(1)
TElem SortedBagIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();
	return this->currentNode->value;
}

