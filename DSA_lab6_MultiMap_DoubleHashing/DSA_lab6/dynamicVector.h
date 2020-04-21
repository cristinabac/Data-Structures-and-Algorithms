#pragma once
#include <assert.h>
template <typename T>

class dynamicVector
{

private:
	T* elems;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	dynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	dynamicVector(const dynamicVector& v);
	~dynamicVector();

	dynamicVector& operator=(const dynamicVector& v);
	T& operator[](int pos);

	void add(T e);
	void remove(int pos);
	void update(int pos, const T& e);
	int find_position(const T& e);

	int getSize() const;

	T* getAllElems() const;

private:
	// Resizes the current dynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);
};




template <typename T>
dynamicVector<T> operator+(dynamicVector<T> v, const T& e);

template <typename T>
dynamicVector<T>  operator+(dynamicVector<T> v, const T & e)
{
	v.add(e);
	return v;
}

template <typename T>
dynamicVector<T> operator+(const T&e, dynamicVector<T> v);

template <typename T>
dynamicVector<T>  operator+(const T & e, dynamicVector<T> v)
{
	v.add(e);
	return v;
}


template <typename T>
dynamicVector<T>::dynamicVector(int capacity)
{
	/*
	Constructor for dynamicVector
	*/
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

template <typename T>
dynamicVector<T>::dynamicVector(const dynamicVector& v)
{
	/*
	Copy constructor for dynamicVector
	*/
	int i;
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
dynamicVector<T>::~dynamicVector()
{
	/*
	Destructor for dynamicVector
	*/
	delete[] this->elems;
}

template <typename T>
dynamicVector<T> & dynamicVector<T>::operator=(const dynamicVector& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}

template<typename T>
inline T & dynamicVector<T>::operator[](int pos)
{
	return this->elems[pos];
}

template <typename T>
void dynamicVector<T>::resize(double factor)
{
	this->capacity *= factor;

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}



template <typename T>
void dynamicVector<T>::add(T e)
{
	/*
	Add an element to the array
	*/
	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
int dynamicVector<T>::getSize() const
{
	return this->size;
}


template <typename T>
void dynamicVector<T>::remove(int pos)
{
	//if (this->elems == NULL)
		//return;
	if (pos < 0 || pos >= this->getSize())
		return;
	for (int i = pos; i < this->getSize() - 1; i++)
		this->elems[i] = this->elems[i + 1];
	this->size--;
}


template <typename T>
int dynamicVector<T>::find_position(const T& e)
{
	//if (this == NULL)
		//return -1;

	for (int i = 0; i < this->getSize(); i++)
	{
		T d = this->elems[i];
		if (d == e)
			return i;
	}
	return -1;
}

template <typename T>
void dynamicVector<T>::update(int pos, const T& e)
{
	this->elems[pos] = e;
}

template <typename T>
T* dynamicVector<T>::getAllElems() const
{
	return this->elems;
}