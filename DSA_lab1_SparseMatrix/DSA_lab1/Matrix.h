#pragma once

#include "dynamicVector.h"

typedef int TElem;

#define NULL_TELEM 0



class Matrix {



private:

	/*representation of the matrix*/
	dynamicVector<int> lines, cols, values;
	int nrC;
	int nrL;

public:

	//constructor

	//throws exception if nrLines or nrCols is negative or zero

	Matrix(int nrL, int nrC);
	~Matrix();


	//returns the number of lines

	int nrLines() const;



	//returns the number of columns

	int nrColumns() const;



	//returns the element from line i and column j (indexing starts from 0)

	//throws exception if (i,j) is not a valid position in the Matrix

	TElem element(int i, int j) const;



	//modifies the value from line i and column j

	//returns the previous value from the position

	//throws exception if (i,j) is not a valid position in the Matrix

	TElem modify(int i, int j, TElem e);
	void print();

	void resize(int newLines, int newCol);


};


