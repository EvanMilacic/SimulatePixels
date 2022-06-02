#pragma once

#include "Field.h"

class FieldController
{
private:
	Field* field;
	int width = 0;
	int height = 0;
	int size = 0;

public:

	FieldController(Field *_field) {
		field = _field;
		size = field->getSize();
		height = field->getHeight();
		width = field->getWidth();
	}

	~FieldController() {}

	//Setters
	void set(Index_t index, MatType type);
	void set(int width, int height, MatType type);
	void set(Index2 ind, MatType type); 
	void clear(Index_t index);
	void clear(int width, int height); 
	void clear(Index2 ind);

	//Getters
	inline int getSize(void);
	inline int getWidth(void); 
	inline int getHeight(void);
	MatType at(int index); 
	MatType at(int width, int height); 
	MatType at(Index2 ind);
	MatType at(int index, Index2 motionVector); 
	MatType at(Index2 ind, Index2 motionVector);

	//Indices Tools
	inline int CalcIndex(int i, int j); 
	int CalcIndex(Index2 ind);
	inline Index2 CalcIndex2(int index);
	Index2 CalcIndex2(int index, Index2 motionVector);


	//Field Operations
	void flip(int index_1, int index_2); 
	void flip(Index2 ind_1, Index2 ind_2);
	void flip(int index, Index2 motionVector); 

};

