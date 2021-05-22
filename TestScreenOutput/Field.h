#pragma once
#include <vector>
#include "Globals.h"
#include "Enums.h"

class Field
{
public:
	int width = 0;
	int height = 0;
	int size = 0;

	std::vector<MatType> typeArray;

	Field() {};
	Field(int _width, int _height) {
		setSize(_width, _height);
	}

	~Field() {};

	int CalcIndex(int i, int j) {
		return width * j + i;
	}

	int CalcIndex(Index2 ind) {
		return CalcIndex(ind.i, ind.j);
	}

	Index2 CalcIndex2(int index) {
		Index2 indices{ (int)(index - floor(index / width) * width), (int)floor(index / width) };
		return indices;
	}

	Index2 CalcIndex2(int index, Index2 motionVector) {
		Index2 ind = CalcIndex2(index);
		ind += motionVector;
		return ind;
	}

	//Setters 
	void setSize(int _width, int _height) {
		width = _width;
		height = _height;
		typeArray.resize(width * height);
		size = typeArray.size();
	}

	//Getters
	int getSize(void) { return typeArray.size(); };
	int getWidth(void) { return width; };
	int getHeight(void) { return height; };

	MatType at(Index2 ind) {
		return at(ind.i, ind.j);
	}

	MatType at(int width, int height) {
		int index = CalcIndex(width, height);
		return at(index);
	}

	MatType at(int index) {
		return typeArray[index];
	}

	MatType at(Index2 ind, Index2 motionVector) {
		int index = CalcIndex(ind);
		return at(index, motionVector);
	}

	MatType at(int index, Index2 motionVector) {
		Index2 ind_dir = CalcIndex2(index, motionVector);
		return at(ind_dir);
	}

	//Operations
	void flip(int index_1, int index_2) {
		MatType temp = typeArray[index_1];
		typeArray[index_1] = typeArray[index_2];
		typeArray[index_2] = temp;
	}
	void flip(Index2 ind_1, Index2 ind_2) {
		int index_1 = CalcIndex(ind_1);
		int index_2 = CalcIndex(ind_2);
		flip(index_1, index_2);
	}
	void flip(int index, Index2 motionVector) {
		Index2 ind = CalcIndex2(index);
		Index2 ind_dir = CalcIndex2(index, motionVector);
		flip(ind, ind_dir);
	}

};

