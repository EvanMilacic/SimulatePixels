#pragma once
#include <cmath>
#include "Defines.h"
#include "Motion2.h"
#include "MyMath.h"

struct Index2 {
	Index_t i;
	Index_t j;

	Index2(Index_t _i = 0, Index_t _j = 0) : i(_i), j(_j) {};

	Index2 operator+(const Index2 other) const{
		Index2 result{ i, j };
		result.i += other.i;
		result.j += other.j;
		return result;
	}

	Index2 operator+(const Motion2 other) const {
		Index2 result{ i, j };
		result += other;
		return result;
	}

	void operator+=(const Index2 other) {
		i += other.i;
		j += other.j;
	}

	void operator+=(const Motion2 other) {
		i = static_cast<Index_t>(fmax(0, i + other.i));
		j = static_cast<Index_t>(fmax(0, j + other.j));
	}

	Index2 operator-(const Index2 other) const {
		Index2 result{ i, j };
		result.i -= other.i;
		result.j -= other.j;
		return result;
	}
	void operator-=(const Index2 other) {
		i -= other.i;
		j -= other.j;
	}

	void operator-=(const Motion2 other) {
		i = static_cast<Index_t>(fmax(0, i - other.i));
		j = static_cast<Index_t>(fmax(0, j - other.j));
	}

	bool operator==(const Index2 other) const {
		Index2 result{ i,j };
		if (result.i == other.i && result.j == other.j) {
			return true;
		}
		return false;
	}

};

