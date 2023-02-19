#pragma once
#include <vector>
#include "Defines.h"

template <typename T>
class LargeVector
{
public:
	LargeVector() {}

	LargeVector(Index_t _size) {
		data.resize(_size);
	}

	//getters
	Index_t size() {
		return data.size();
	}

	double at(Index_t index) {
		return data[index];
	}

	//setters
	void set(Index_t index, T value) {
		data[index] = value;
	}

	void resize(Index_t size) {
		data.resize(size);
	}

	void clear(void) {
		data.clear();
	}

private:
	std::vector<T> data;
};

