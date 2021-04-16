#include "Domain.h"

namespace simulate {

	bool Domain::move(int index, MoveDirs dir) {

		materie::MatType myType = field[index];
		Index2 indices = CalcIndex2(index);

		switch (dir) {
		case MoveDirs::Down: {
			
		}break;
		}
	}

	bool Domain::move(int index, MoveDirs dir, int stepLength) {

	}

}