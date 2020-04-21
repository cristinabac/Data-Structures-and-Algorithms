#include "SortedMap.h"
#include "SMIterator.h"
#include <iostream>

//theta(1)
SortedMap::SortedMap(Relation rel)
{
	this->r = rel;	
	this->head = NULL;
}

//Complexity O(number of keys)
TValue SortedMap::add(TKey c, TValue v)
{
	//std::cout <<"---"<< c << " " << v << std::endl;
	//this->printAll();
	if (this->head == NULL)
	{
		Node* node = new Node;
		node->info = TElem(c, v);
		node->next = NULL;
		this->head = node;
		return NULL_TVALUE;
	}
	else
	{
		if (this->search(c) == NULL_TVALUE)
		{
			//add 
			Node* node = new Node;
			Node*prev = new Node;
			node->info = TElem(c, v);

			Node* n = new Node;
			n = this->head;
			prev = NULL;
			while (n != NULL && this->r(n->info.first, c))
			{
				prev = n;
				n = n->next;
			}
			
			if (prev != NULL)
			{
				node->next = n;
				prev->next = node;
				return NULL_TVALUE;
			}
			else
			{
				this->head = node;
				node->next = n;
				return NULL_TVALUE;
			}

		}
		else
		{
			//std::cout << "gasit"<<std::endl;
			Node* n = new Node;
			n = this->head;
			while (n != NULL && n->info.first != c && this->r(n->info.first, c))
				n = n->next;
			//change n with new node
			TValue val = n->info.second;
			n->info.second = v;
			return val;
		}
	}
}


//Complexity O(number of keys)
TValue SortedMap::search(TKey c) const
{
	Node* n = new Node;
	n = this->head;
	while (n != NULL && n->info.first != c && this->r(n->info.first, c))
	{
		n = n->next;
	}
	if (n == NULL || n->info.first != c)
		return NULL_TVALUE;
	return n->info.second;
}

//O(number of keys)
TValue SortedMap::remove(TKey c)
{
	if (this->search(c) == NULL_TVALUE)
		return NULL_TVALUE;
	else
	{
		Node* n = new Node;
		Node *prev = new Node;
		n = this->head;
		prev = NULL;
		while (n->info.first != c)
		{
			prev = n;
			n = n->next;
		}
		//remove node n
		TValue val = n->info.second;
		if (prev == NULL)
			this->head = n->next;
		else
			prev->next = n->next;
		free(n);
		return val;
	}
}

//theta(number of keys)
int SortedMap::size() const
{
	int len = 0;
	Node *n = this->head;
	if (n == NULL)
		return len;
	while (n != NULL)
	{
		n = n->next;
		len++;
	}
	return len;
}

//theta(1)
bool SortedMap::isEmpty() const
{
	if (this->head == NULL)
		return true;
	return false;
}

//theta(1)
SMIterator SortedMap::iterator() const
{
	return SMIterator(*this);
}


//Not important :)
void SortedMap::printAll()
{
	Node* n = new Node;
	n = this->head;
	while (n != NULL)
	{
		std::cout << n->info.first << " " << n->info.second << std::endl;
		n = n->next;
	}
	std::cout << std::endl;
}

//theta(number of keys)
SortedMap::~SortedMap()
{
	
	while (this->head != NULL)
	{
		Node *n = this->head;
		this->head = n->next;
		free(n);
	}
	
}
