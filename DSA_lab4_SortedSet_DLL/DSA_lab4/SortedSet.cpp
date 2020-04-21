#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

//Complexity: theta(capacity)
SortedSet::SortedSet(Relation r)
{
	this->r = r;
	this->head = -1;
	this->tail = -1;
	this->sizee = 0;
	this->firstEmpty = 0;
	this->capacity = 5;
	this->nodes = new dllaNode[this->capacity];
	for (int i = 0; i < this->capacity-1; i++)
		this->nodes[i].next = i+1;
	for (int i = 1; i < this->capacity; i++)
		this->nodes[i].prev = i-1;
	this->nodes[this->capacity - 1].next = -1;
	this->nodes[0].prev = -1;

}

//Complexty: O(n), n-the number of elements in the set
bool SortedSet::add(TComp e)
{
	//if (search(e) == true)
	//	return false;
	if (this->firstEmpty == -1) //resize
	{
		dllaNode* newNodes = new dllaNode[this->capacity * 2];
		for (int idx = 0; idx < this->capacity; idx++)
			newNodes[idx] = this->nodes[idx];

		for (int idx = this->capacity ; idx < this->capacity * 2 - 1; idx++)
			newNodes[idx].next = idx + 1;
		newNodes[this->capacity * 2 - 1].next = -1;

		for (int idx = this->capacity ; idx < this->capacity * 2 ; idx++)
			newNodes[idx].prev = idx - 1;

		delete[] this->nodes;
		this->nodes = newNodes;
		this->firstEmpty = this->capacity;
		this->capacity *= 2;
	}

	int current = this->head; //find the position where we have to put the element
	int prev = -1;
	while (current != -1 && this->r(this->nodes[current].info, e) && this->nodes[current].info != e)
	{
		prev = current;
		current = this->nodes[current].next;
	}

	if (prev == -1) // this means the element will be the head, or the set is empty
	{
		if (current == -1) //the set is empty
		{
			this->head = this->firstEmpty;
			this->tail = this->firstEmpty;
			this->firstEmpty = this->nodes[this->head].next;
			this->nodes[this->head].info = e;
			this->nodes[this->head].next = -1;
			this->nodes[this->head].prev = -1;
			this->sizee++;
			return true;
		}
		else //prev = -1 and current !=-1 => the set is not empty, the element e will be the head
		{
			if (this->nodes[current].info == e)
				return false;
			int pos = this->firstEmpty;
			this->firstEmpty = this->nodes[this->firstEmpty].next;
			this->nodes[pos].info = e;
			this->nodes[pos].next = this->head;
			this->nodes[pos].prev = -1;
			this->nodes[this->head].prev = pos;
			this->head = pos;
			this->sizee++;
			return true;
		}
	}
	else //prev != -1
	{
		if (current == -1) //the element e will be the tail
		{
			if (this->nodes[current].info == e)
				return false;
			int pos = this->firstEmpty;
			this->firstEmpty = this->nodes[this->firstEmpty].next;
			this->nodes[pos].info = e;
			this->nodes[pos].next = -1;
			this->nodes[pos].prev = prev;
			this->nodes[prev].next = pos;
			this->tail = pos;
			this->sizee++;
			return true;
		}
		else // both current and prev != -1, so we are somewhere inside the set
		{
			if (this->nodes[current].info == e)
				return false;
			//put the element e on the current position
			int pos = this->firstEmpty;
			this->firstEmpty = this->nodes[this->firstEmpty].next;

			this->nodes[prev].next = pos;

			this->nodes[pos].info = e;
			this->nodes[pos].next = current;
			this->nodes[pos].prev = prev;

			this->nodes[current].prev = pos;
			this->sizee++;
			return true;
		}
	}
}

//Complexty: O(n), n-the number of elements in the set
bool SortedSet::remove(TComp e)
{
	int current = this->head;
	int prev = -1;

	while (current != -1 and this->nodes[current].info != e and this->r(this->nodes[current].info, e))
	{
		prev = current;
		current = this->nodes[current].next;
	}
	if (current == -1 or this->nodes[current].info != e)
		return false;

	if (prev == -1)
	{
		//the element to be removed is the head
		this->head = this->nodes[this->head].next;
		if (this->head != -1) //still have elements in set
			this->nodes[this->head].prev = -1;
		this->nodes[current].next = this->firstEmpty;
		this->firstEmpty = current;
		this->nodes[current].prev = -1;
		this->sizee--;
		return true;
	}
	else
	{
		if (current == this->tail)
		{
			this->tail = this->nodes[current].prev;
			this->nodes[this->tail].next = -1;
			this->nodes[current].next = this->firstEmpty;
			this->nodes[current].prev = -1;
			this->firstEmpty = current;
			this->sizee--;
			return true;
		}
		else //we are inside the set
		{
			this->nodes[prev].next = this->nodes[current].next;
			this->nodes[this->nodes[current].next].prev = prev;

			this->nodes[current].next = this->firstEmpty;
			this->nodes[current].prev = -1;
			this->firstEmpty = current;
			this->sizee--;
			return true;
		}
	}
}


//complexity O(n), n-the number of elements in the set
bool SortedSet::search(TElem elem) const
{
	int current = this->head;
	while (current != -1 and this->nodes[current].info != elem and this->r(this->nodes[current].info,elem))
		current = this->nodes[current].next;
	if (current == -1 or this->nodes[current].info != elem)
		return false;
	else
		return true;

}

//Complexity theta(1)
int SortedSet::size() const
{
	return this->sizee;
}


//Complexity theta(1)
bool SortedSet::isEmpty() const
{
	if (this->sizee == 0)
		return true;
	return false;
}

SortedSetIterator SortedSet::iterator() const
{
	return SortedSetIterator(*this);
}

//my function, just for testing :)
void SortedSet::print()
{
	for (int i = 0; i < this->sizee; i++)
		std::cout << this->nodes[i].info << " ";
	std::cout << endl;
	for (int i = 0; i < this->sizee; i++)
		std::cout << this->nodes[i].prev << " ";
	std::cout << endl;
	for (int i = 0; i < this->sizee; i++)
		std::cout << this->nodes[i].next << " ";
	std::cout << endl;
}


SortedSet::~SortedSet()
{
	delete[] this->nodes;
}

