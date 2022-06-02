#include "FieldController.h"

//Setters
void FieldController::set(Index_t index, MatType type) {
	field->set(index, type);
}

void FieldController::set(int width, int height, MatType type) {
	int index = CalcIndex(width, height);
	field->set(index, type);
}

void FieldController::set(Index2 ind, MatType type) {
	int index = CalcIndex(ind.i, ind.j);
	field->set(index, type);
}

void FieldController::clear(Index_t index) {
	field->set(index, MatType::Default);
}

void FieldController::clear(int width, int height) {
	int index = CalcIndex(width, height);
	field->set(index,MatType::Default);
}

void FieldController::clear(Index2 ind) {
	int index = CalcIndex(ind.i, ind.j);
	field->set(index, MatType::Default);
}

//Getters

inline int FieldController::getSize(void) { return size; }

inline int FieldController::getWidth(void) { return width; }

inline int FieldController::getHeight(void) { return height; }

MatType FieldController::at(int index) {return field->at(index);}

MatType FieldController::at(int width, int height) {
	int index = CalcIndex(width, height);
	return at(index);
}

MatType FieldController::at(Index2 ind) { return at(ind.i, ind.j); }

MatType FieldController::at(int index, Index2 motionVector) {
	Index2 ind_dir = CalcIndex2(index, motionVector);
	return at(ind_dir);
}

MatType FieldController::at(Index2 ind, Index2 motionVector) {
	int index = CalcIndex(ind);
	return at(index, motionVector);
}

//Indices Tools

inline int FieldController::CalcIndex(int i, int j) {
	return width * j + i;
}

int FieldController::CalcIndex(Index2 ind) {
	return CalcIndex(ind.i, ind.j);
}

inline Index2 FieldController::CalcIndex2(int index) {
	Index2 indices{ (int)(index - floor(index / width) * width), (int)floor(index / width) };
	return indices;
}

Index2 FieldController::CalcIndex2(int index, Index2 motionVector) {
	Index2 ind = CalcIndex2(index);
	ind += motionVector;
	return ind;
}


//Operations

void FieldController::flip(int index_1, int index_2) {
	MatType temp = field->at(index_1);
	field->set(index_1,field->at(index_2));
	field->set(index_2, temp);
}
void FieldController::flip(Index2 ind_1, Index2 ind_2) {
	int index_1 = CalcIndex(ind_1);
	int index_2 = CalcIndex(ind_2);
	flip(index_1, index_2);
}
void FieldController::flip(int index, Index2 motionVector) {
	Index2 ind = CalcIndex2(index);
	Index2 ind_dir = CalcIndex2(index, motionVector);
	flip(ind, ind_dir);
}

bool FieldController::isDefault(Index_t index) {
	return (field->at(index) == MatType::Default);
}