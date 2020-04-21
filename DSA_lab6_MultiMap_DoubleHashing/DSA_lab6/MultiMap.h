#pragma once

#include<vector>

#include<utility>

#include <limits.h>

#include "dynamicVector.h"

using namespace std;

#define DELETED INT_MAX
#define MY_NULL INT_MIN

typedef int TKey;

typedef int TValue;



typedef std::pair<TKey, TValue> TElem;



struct Node {
	TKey key;
	dynamicVector<TValue> values;
};



class MultiMap

{
	friend class MultiMapIterator;

private:

	/* representation of the MultiMap */
	int m;   //the size of the hash table
	int h(int k, int i) const { 
		if (k > 0)
			return  (k % m + i * (1 + (k % (m - 1)))) % m;
		else
			return  ((m+(k%m)) % m + i * (1 + ((m-1) + k % (m - 1))%(m-1))) % m;
	}
	Node* hash;
	int nrElems;   //the number of elements in the multimap

	int primes[18];   //posibilele m -uri
	int posPrime;     //pozitia lui m din vectorul primes



public:

	//constructor

	MultiMap();



	//adds a key value pair to the multimap

	void add(TKey c, TValue v);



	//removes a key value pair from the multimap

	//returns true if the pair was removed (if it was in the multimap) and false otherwise

	bool remove(TKey c, TValue v);



	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty

	vector<TValue> search(TKey c) const;



	//returns the number of pairs from the multimap

	int size() const;



	//checks whether the multimap is empty

	bool isEmpty() const;



	//returns an iterator for the multimap

	MultiMapIterator iterator();



	//descturctor

	~MultiMap();

	//my function , not important :)
	void print();
private:
	void resize();
	



};


