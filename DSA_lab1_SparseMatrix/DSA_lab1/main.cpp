#include <iostream>
#include "dynamicVector.h"
#include "Matrix.h"
#include <assert.h>
using namespace std;

void testAll() {
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == 0);
}

void testCreate() {
	Matrix m(10, 10);
	assert(m.nrLines() == 10);
	assert(m.nrColumns() == 10);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			assert(m.element(i, j) == 0);
}

void testModify() {
	Matrix m(10, 10);
	for (int j = 0; j < m.nrColumns(); j++)
		m.modify(4, j, 3);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i == 4)
				assert(m.element(i, j) == 3);
			else
				assert(m.element(i, j) == 0);
}

void testQuantity() {
	Matrix m(300, 300);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				m.modify(i, j, i*j);
			else
				if (j % 3 == 0)
					m.modify(i, j, i + j);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				assert(m.element(i, j) == i * j);
			else
				if (j % 3 == 0)
					assert(m.element(i, j) == i + j);
				else assert(m.element(i, j) == 0);
}

void testExceptions() {
	Matrix m(10, 10);
	try {
		m.element(-10, 0);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		m.modify(12, 0, 1);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		assert(m.nrLines());
	}
	catch (exception&) {
		assert(false);
	}
}



void testAllExtended() {
	testCreate();
	testModify();
	testQuantity();
	testExceptions();
}


void my_test() {
	Matrix m(10, 10);
	for (int j = 0; j < m.nrColumns(); j++)
		m.modify(4, j, 3);
	m.print();
	m.resize(15, 15);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (i == 4)
				assert(m.element(i, j) == 3);
			else
				assert(m.element(i, j) == 0);
	m.print();
	m.modify(12, 12, 66);
	m.print();
	m.resize(15, 5);
	m.print();
}

int main()
{
	testAll();
	testAllExtended();
	//my_test();
	system("pause");
	return 0;
	
}