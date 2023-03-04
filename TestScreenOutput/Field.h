#pragma once

#include "Defines.h"
#include "LargeVector.h"
#include "FieldData.h"
#include "Index2.h"

template <typename T>
class Field
{
public:

	Field() {
	}

	Field(FieldData _fieldData) {
		fieldData = _fieldData;
		data.resize(fieldData.Size);
	}

	//getters
	Index_t size(void) {
		return data.size();
	}

	T at(Index_t index) {
		return data.at(index);
	}

	T at(Index2 ind) {
		return data.at(convIndex(ind.i, ind.j));
	}


	//setters
	void resize(FieldData _fieldData) {
		fieldData = _fieldData;
		data.resize(fieldData.Size);
	}

	void set(Index_t index, T value) {
		data.set(index, value);
	}

	void set(Index_t _i, Index_t _j, T value) {
		data.set(convIndex(_i, _j), value);
	}

	void set(Index2 ind, T value) {
		data.set(convIndex(ind.i, ind.j), value);
	}

	void clear(void) {
		fieldData.clear();
		data.clear();
	}

private:

	inline Index_t convIndex(Index_t i, Index_t j) {
		return i + fieldData.Nx *j ;
	}

	FieldData fieldData = { 0,0,0 };
	LargeVector<T> data;
};

