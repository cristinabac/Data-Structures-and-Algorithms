#pragma once
using namespace std;


typedef int TElem;

typedef TElem TComp;



typedef bool(*Relation)(TComp, TComp);

struct dllaNode {
	TElem info;
	int next;
	int prev;
};



class SortedSet {

	friend class SortedSetIterator;

private:

	/*Representation of the SortedSet*/
	Relation r;
	dllaNode* nodes;
	int capacity;
	int head;
	int tail;
	int firstEmpty;
	int sizee;

public:

	//constructor

	SortedSet(Relation r);



	//adds an element to the sorted set

	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 

	//it returns false

	bool add(TComp e);





	//removes an element from the sorted set

	//if the element was removed, it returns true, otherwise false

	bool remove(TComp e);



	//checks if an element is in the sorted set

	bool search(TElem elem) const;





	//returns the number of elements from the sorted set

	int size() const;



	//checks if the sorted set is empty

	bool isEmpty() const;



	//returns an iterator for the sorted set

	SortedSetIterator iterator() const;



	// destructor

	~SortedSet();


	void print();


};


