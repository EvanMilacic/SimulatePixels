#pragma once
#include <Windows.h>

struct RenderState {
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;
};

struct Index2 {
	int i;
	int j;

	Index2(int _i = 0, int _j = 0) : i(_i), j(_j) {};

	Index2 operator+(const Index2 other) const{
		Index2 result{ i, j };
		result.i += other.i;
		result.j += other.j;
		return result;
	}

	void operator+=(const Index2 other) {
		i += other.i;
		j += other.j;
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
	bool operator==(const Index2 other) const {
		Index2 result{ i,j };
		if (result.i == other.i && result.j == other.j) {
			return true;
		}
		return false;
	}

};

