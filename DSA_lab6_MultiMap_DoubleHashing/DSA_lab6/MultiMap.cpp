#include "MultiMap.h"
#include "MultiMapIterator.h"

#include <iostream>


//theta(m)   -> for initializing the hash
//m is the size of the hash
MultiMap::MultiMap()
{
	int prime_numbers[] = { 11, 23, 47, 97, 197, 397, 853, 1709, 3433, 6203, 12409, 25153, 50951, 100003, 200003, 400009, 800011, 1600033 };
	for (int i = 0; i < 18; i++)
		this->primes[i] = prime_numbers[i];
	this->posPrime = 0; //the position of m in the vector of prime numbers used when we need a resize: we go to the next prime number as the size of the hash

	this->m = this->primes[this->posPrime]; 
	this->nrElems = 0;
	this->hash = new Node[this->m];
	for (int i = 0; i < this->m; i++)
		this->hash[i].key = MY_NULL;  //initialize each element from the hash with a null value

}

//BC: theta(1)
//AC: theta(1)    ->theta(1) amortizat
//WC: theta(m)
//Complexity O(m)
void MultiMap::add(TKey c, TValue v)
{
	int i = 0;
	int pos = this->h(c, i);
	int pos_deleted = -1;
	while (i < this->m && this->hash[pos].key != MY_NULL && this->hash[pos].key != c)
	{
		if (this->hash[pos].key == DELETED)
			pos_deleted = pos;
		i++;
		pos = this->h(c, i);
	}
	if (this->hash[pos].key == c)
	{
		// we have that key in the hash
		// we have to add the value to the list of values of the key
		this->hash[pos].values.add(v);
		this->nrElems++;
	}
	else if (pos_deleted != -1) //the key is not in the hash, but we had a deleted position where i can put it; also
		//i don t need a resize
	{
		this->hash[pos_deleted].key = c;
		this->hash[pos_deleted].values.add(v);
		this->nrElems++;
	}
	else
	{
		//we do not have the key in the multimap and we might need a resize
		if (i == this->m)       //if ((float)this->nrElems / this->m > 0.75)// ->if load factor is 0.75 => 1/(1-0.75) = 1/0.25 = 4 maximum steps (nr maxim de verificari) for unsuccesfull search and add(insert)
		{
			//if we need resize
			this->resize();
			this->add(c, v);
		}
		else
		{
			//if we do not need resize
			//we put on the position pos the key with its value
			this->hash[pos].key = c;
			this->hash[pos].values.add(v);
			this->nrElems++;
		}

		//this->nrElems++;
		
	}
}

//BC: theta(1)
//AC: theta(1)
//WC: theta(m)
//Complexity O(m)
bool MultiMap::remove(TKey c, TValue v)
{
	int i = 0;
	int pos = this->h(c, i); //find the position of the key if it exits
	while (i < this->m && this->hash[pos].key != MY_NULL && this->hash[pos].key != c) 
	{
		i++;
		pos = this->h(c, i);
	}
	if (this->hash[pos].key == c)
	{
		int pos_of_val = this->hash[pos].values.find_position(v);
		if (pos_of_val == -1)
		{
			return false; //the pair is not in the map  (the value is not in the list of the key)
		}
		//the pair is in the map
		this->hash[pos].values.remove(pos_of_val);
		//verify if the vector of values of k remained empty and mark the position by DELETED
		if (this->hash[pos].values.getSize() == 0)
			this->hash[pos].key = DELETED;
		this->nrElems--;
		return true;
	}
	return false; //the pair key, value was not in the multimap
}

//BC: theta(1)    ->no collisions
//AC: theta(1)    ->theta(1) amortizat
//WC: theta(m)   ->we have to probe over all m elements
//					- ?not theta(nr of unique keys)? bc in wors case the first (nr of unique keys) positions from the permutation of our element are occupied by other elements
//					- NO - bc we may have deleted elements in the hash.... so, if all m-1 first possible positions were occupied and then deleted, we can search through the whole hash
//Complexity O(m)
vector<TValue> MultiMap::search(TKey c) const
{
	if (this->nrElems == 0)
	{
		std::vector<TValue> gol;
		return gol;
	}

	int i = 0;
	int pos = this->h(c, i);
	while (i < this->m && this->hash[pos].key != MY_NULL && this->hash[pos].key != c)
	{
		i++;
		pos = this->h(c, i);
	}
	if (this->hash[pos].key == c)
	{
		// we have that key in the hash, return its list of values
		std::vector<TValue> vct;
		for (int j = 0; j < this->hash[pos].values.getSize(); j++)
			vct.push_back(this->hash[pos].values[j]);
		return vct;
	}
	//we do not have the element in the hash, return an empty vector
	std::vector<TValue> gol;
	return gol;
}


//theta(1)
int MultiMap::size() const
{
	return this->nrElems;
}

//theta(1)
bool MultiMap::isEmpty() const
{
	return this->nrElems == 0;
}


//theta(1)
MultiMapIterator MultiMap::iterator()
{
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap()
{
}

//theta(new capacity) -> because we need to pass through all the new hash and initialize it by MY_NULL
void MultiMap::resize()
{
	/* Resize operation for the hashtable that rehashes the elements. */

	this->posPrime++;
	int old_m = this->m;
	Node* new_table = new Node[this->primes[this->posPrime]];
	this->m = this->primes[this->posPrime];

	for (int i = 0; i < this->m; i++)
		new_table[i].key = MY_NULL;

	for (int index = 0; index < old_m; index++) 
	{
		TKey c = this->hash[index].key;
		if (c != MY_NULL && c != DELETED)
		{
			dynamicVector<TValue> v = this->hash[index].values;
			for (int i = 0; i < this->m; i++)
				if (new_table[this->h(c, i)].key == MY_NULL)
				{
					new_table[this->h(c, i)].key = c;
					//new_table[this->h(c, i)].values = v;
					for (int t = 0; t < v.getSize(); t++)
						new_table[this->h(c, i)].values.add(v[t]);
					break;
				}
		}
	}
	delete[] this->hash;
	this->hash = new_table;
	
}

void MultiMap::print()
{
	std::cout << "---------------------"<<endl;
	std::cout << this->m << endl;
	std::cout << this->nrElems<<endl;
	for (int i = 0; i < this->m; i++)
	{
		std::cout << this->hash[i].key << " ";
		if (this->hash[i].key == -83)
			for (int j = 0; j < this->hash[i].values.getSize(); j++)
				cout << endl << this->hash[i].values[j] << endl;
	}
	std::cout <<endl<< "---------------------" << endl;
}
