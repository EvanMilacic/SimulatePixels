#pragma once

#include "Defines.h"

struct Motion2 {
	int i;
	int j;

	Motion2(int _i = 0, int _j = 0) : i(_i), j(_j) {};

	Motion2 operator+(const Motion2 other) const {
		Motion2 result{ i, j };
		result.i += other.i;
		result.j += other.j;
		return result;
	}

	void operator+=(const Motion2 other) {
		i += other.i;
		j += other.j;
	}

	Motion2 operator-(const Motion2 other) const {
		Motion2 result{ i, j };
		result.i -= other.i;
		result.j -= other.j;
		return result;
	}
	void operator-=(const Motion2 other) {
		i -= other.i;
		j -= other.j;
	}
	bool operator==(const Motion2 other) const {
		Motion2 result{ i,j };
		if (result.i == other.i && result.j == other.j) {
			return true;
		}
		return false;
	}
};

