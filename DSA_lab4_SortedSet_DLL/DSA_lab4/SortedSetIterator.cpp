#include "SortedSetIterator.h"
#include <exception>

SortedSetIterator::SortedSetIterator(const Container& c) :
	c{ c }
{
	this->current=c.head;
}

void SortedSetIterator::first()
{
	//theta(1)
	this->current = c.head;
}

void SortedSetIterator::next()
{
	//theta(1)
	if (this->valid() == true)
		this->current = this->c.nodes[current].next;
	else throw std::exception();
}

bool SortedSetIterator::valid() const
{
	//theta(1)
	if (this->current == -1)
		return false;
	else
		return true;
}

TElem SortedSetIterator::getCurrent() const
{
	//theta(1)
	if (this->valid())
		return this->c.nodes[current].info;
	else throw std::exception();
}

//O(k)
void SortedSetIterator::jumpBackward(int k)
{
	if (!this->valid())
		throw std::exception();
	for (int i = 1; i <= k; i++)
		if (this->current != -1)
			this->current = this->c.nodes[this->current].prev;
		else
			break;
}










SortedSetIterator::~SortedSetIterator()
{
}

