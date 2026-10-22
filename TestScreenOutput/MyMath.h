#pragma once
#include <cmath>
#include <cstdlib>

namespace math {

	inline int clamp(int min, int val, int max) {
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	inline bool randomBool() {
		return (std::rand() % 2 == 1)? true : false ;
	}

}