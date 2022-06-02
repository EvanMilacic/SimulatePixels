#pragma once
#include <Windows.h>
#include <vector>
#include "Enums.h"
#include "UserDefs.h"

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

struct LUT_MotionVector {

	Index2 get(MoveDirs direction) {
		switch (direction) {
		case MoveDirs::Down: {
			Index2 motion = { 0,-1 };
			return motion; }
		case MoveDirs::Up: {
			Index2 motion = { 0,1 };
			return motion; }
		case MoveDirs::Left: {
			Index2 motion = { -1,0 };
			return motion; }
		case MoveDirs::Right: {
			Index2 motion = { 1,0 };
			return motion; }
		case MoveDirs::LeftD: {
			Index2 motion = { -1,-1 };
			return motion; }
		case MoveDirs::LeftU: {
			Index2 motion = { -1,1 };
			return motion; }
		case MoveDirs::RightD: {
			Index2 motion = { 1,-1 };
			return motion; }
		case MoveDirs::RightU: {
			Index2 motion = { 1,1 };
			return motion; }
		default: {
			Index2 motion = { 0,0 };
			return motion; }
		}
	}

};

struct DecompositionData {
	Index2 fieldSize;
	Index2 subFieldSize;
	
	Index_t numberOfSubDivisions = 0;
	Index2 divisionFieldSizes;

	std::vector<Index_t> tags;
	std::vector<Index2> subOrigins;
	std::vector<Index2> subSizes;

	void resizeArrays(void) {
		if (numberOfSubDivisions > 0) {
			tags.resize(this->numberOfSubDivisions);
			subOrigins.resize(this->numberOfSubDivisions);
			subSizes.resize(this->numberOfSubDivisions);
		}
	}

};