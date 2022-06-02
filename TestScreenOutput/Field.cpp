#include "Field.h"

inline void Field::set(int index, MatType type) { typeArray[index] = type; }

void Field::setSize(int _width, int _height) {
	width = _width;
	height = _height;
	typeArray.resize(width * height);
	size = typeArray.size();
}

//Getters
int Field::getSize(void) { return typeArray.size(); };
int Field::getWidth(void) { return width; };
int Field::getHeight(void) { return height; };

MatType Field::at(int index) {
	return typeArray[index];
}
