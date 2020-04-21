#include "SMIterator.h"
#include <exception>

SMIterator::SMIterator(const Container& c):
	c{c},current{c.head}
{
	//this->current=c.head;
}

void SMIterator::first()
{
	//theta(1)
	this->current = c.head;
}

void SMIterator::next()
{
	//theta(1)
	if (this->valid() == true)
		this->current = current->next;
	else throw std::exception();
}

bool SMIterator::valid() const
{
	//theta(1)
	if (this->current == NULL)
		return false;
	else
		return true;
}

TElem SMIterator::getCurrent() const
{
	//theta(1)
	if (this->valid())
		return this->current->info;
	else throw std::exception();
}

SMIterator::~SMIterator()
{
}
