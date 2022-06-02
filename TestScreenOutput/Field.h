#pragma once
#include <vector>
#include "Globals.h"
#include "Enums.h"

class Field
{
private:
	int width = 0;
	int height = 0;
	int size = 0;

	std::vector<MatType> typeArray;

public:

	Field() {};
	Field(int _width, int _height) {
		setSize(_width, _height);
	}

	~Field() {};

	//Setters 
	inline void set(int index, MatType type); 
	void setSize(int _width, int _height); 

	//Getters
	int getSize(void); 
	int getWidth(void); 
	int getHeight(void); 
	MatType at(int index); 


};

