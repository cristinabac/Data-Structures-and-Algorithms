#include "Matrix.h"
#include "dynamicVector.h"
#include <exception>
#include <iostream>
using namespace std;

//thteta(nr_cols)
Matrix::Matrix(int nrLines, int nrCols)
{
	if (nrLines <= 0 || nrCols <= 0)
		throw std::exception();
	this->nrC = nrCols;
	this->nrL = nrLines;
	for (int i = 0; i <= nrCols; i++)
		this->cols.add(0);
	//this->lines.add(0);
	//this->values.add(0);
	
}

//theta(1)
int Matrix::nrLines() const
{
	return this->nrL;
}


//theta(1)
int Matrix::nrColumns() const
{
	return this->nrC;
}


//O(number of non zero elements in matrix on the column j)
TElem Matrix::element(int i, int j) const
{
	int index;
	if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC)
		throw std::exception();
	for (index = this->cols.getAllElems()[j]; index < this->cols.getAllElems()[j+1]; index++)
	{
		if (this->lines.getAllElems()[index] == i)
			return this->values.getAllElems()[index];
	}
	return 0; //there is no element on position i,j
}

//O(number of non zero elements in matrix)
TElem Matrix::modify(int i, int j, TElem e)
{
	if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC)
		throw std::exception();
	if (this->element(i, j) == 0)
	{
		for (int t = j + 1; t <= this->nrC; t++)
			this->cols[t]++;
		int start_pos = this->cols[j];
		int final_pos = this->cols[j + 1] - 2;
		while (i > this->lines[start_pos] && start_pos<=final_pos)
			start_pos++;
		///put i in lines on pos start_pos
		this->lines.add(0);
		this->values.add(0);
		for (int t = this->lines.getSize()-1; t > start_pos; t--)
		{
			this->lines.getAllElems()[t] = this->lines.getAllElems()[t - 1];
			this->values.getAllElems()[t] = this->values.getAllElems()[t - 1];
		}
		this->lines.getAllElems()[start_pos] = i;
		this->values.getAllElems()[start_pos] = e;
	}
	else if(e==0) //remove 
	{
		int idx = -1;
		for (int index = this->cols.getAllElems()[j]; index < this->cols.getAllElems()[j + 1]; index++)
			if (this->lines.getAllElems()[index] == i)
				idx = index;
		if (idx != -1)
		{
			this->lines.remove(idx);
			this->values.remove(idx);
			for (int t = j; t <= this->nrC; t++)
				this->cols.getAllElems()[t]--;

		}
	}
	else //only modify
	{
		for (int index = this->cols.getAllElems()[j]; index < this->cols.getAllElems()[j + 1]; index++)
			if (this->lines.getAllElems()[index] == i)
				this->values.getAllElems()[index] = e;
	}
}

void Matrix::print()
{
	for (int i = 0; i < this->nrC; i++)
		cout << this->cols[i] <<" ";
	cout << endl;
	for (int i = 0; i <= this->lines.getSize()-1; i++)
		cout << this->lines[i]<<" ";
	cout << endl;
	for (int i = 0; i <= this->values.getSize()-1; i++)
		cout << this->values[i]<<" ";
	cout << endl << endl;
}

void Matrix::resize(int newLines, int newCol)
{
	if (newLines <= 0 || newCol <= 0)
		throw std::exception();
	if (newCol < this->nrC)
	{
		int pos = this->cols[newCol + 1];
		while (pos < this->lines.getSize())
		{
			this->lines.remove(pos);
			this->values.remove(pos);
			pos++;
		}
		for (int i = newCol; i < nrC; i++)
		{
			
			this->cols.remove(i);
		}
		
		this->nrC = newCol;
	}
	else if(newCol > this->nrC)
	{
		int val_toate = this->cols[nrC];
		for (int i = nrC + 1; i <= newCol; i++)
			this->cols.add(val_toate);
		this->nrC = newCol;
	}


	if (newLines > this->nrL)
		this->nrL = newLines;
	else if (newLines < this->nrL)
	{
		for(int i=0;i<=this->nrC;i++)
			for(int j=0;j<this->lines.getSize();j++)
				if (this->lines[j] > newLines && this->element(this->lines[j],i)!=0)
				{
					TElem val = this->modify(this->lines[j], i, 0);
				}
		this->nrL = newLines;
	}


}

Matrix::~Matrix()
{
}