#include "Domain.h"

namespace simulate {

	bool Domain::move(int index, MoveDirs dir) {
		//Get Motion vector
		Index2 motion = getMotionVector(dir);
		//Calculate the target cell
		Index_t targetIndex = getDirIndex(index, motion);
		//If cell is not occupied, move there
		if (isDefault(targetIndex)) {
			MatType temp = field[index];
			field[index] = MatType::Default;
			field[targetIndex] = temp;
			return true;
		}
		else {
			//If occupied, return false
			return false;
		}

	}

	bool Domain::move(int index, MoveDirs dir, int stepLength) {

		Index_t workingIndex, targetIndex;
		workingIndex = index;
		targetIndex = index;
		//Get motion vector
		Index2 motion = getMotionVector(dir);

		//Loop over the length of the vector
		//If an obstructed cell is found, the cell will only be moved until that cell
		for (int n = 0; n < stepLength; n++) {
			//Get target cell id
			targetIndex = getDirIndex(workingIndex, motion);
			//Check if it is empty
			if (isDefault(targetIndex)) {
				//If empty, prepare for next step
				workingIndex = targetIndex;
			}else if( !isDefault(targetIndex) && n > 0) {
				//If vector obstructed
				break;
			}else{
				//If cell occupied
				return false;
			}
		}

		//Move cell to target location
		MatType temp = field[index];
		field[index] = MatType::Default;
		field[targetIndex] = temp;
		//Provide succes boolean
		return true;
	}

	Index_t Domain::getDirIndex(Index_t index, Index2 motion) {

		Index2 currentInd = CalcIndex2(index);
		Index2 newInd;

		//Move index along the motion vector
		newInd.i = currentInd.i + motion.i;
		newInd.j = currentInd.j + motion.j;

		//Avoid going out of the domain size
		newInd.i = math::clamp(0, newInd.i, nWidth-1);
		newInd.j = math::clamp(0, newInd.j, nHeight - 1);

		//Convert 2D inex to 1D
		return CalcIndex(newInd);

	}

	Index2 Domain::getMotionVector(MoveDirs dir) {
		// produces the correct motion vector in the grid
		switch (dir) {
		case MoveDirs::Down: {
			Index2 motion = { 0,-1 };
			return motion; }
		case MoveDirs::Up: {
			Index2 motion = { 0,1 };
			return motion; }
		case MoveDirs::Left: {
			Index2 motion = {-1,0 };
			return motion; }
		case MoveDirs::Right: {
			Index2 motion = {1,0};
			return motion; }
		case MoveDirs::LeftD: {
			Index2 motion = { -1,-1 };
			return motion; }
		case MoveDirs::LeftU: {
			Index2 motion = { -1,1};
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

	bool Domain::isOnEdge(Index_t index) {
		Index2 ind = CalcIndex2(index);
		if (ind.i == 0 || ind.i == nWidth) {
			return true;
		}
		if (ind.j == 0 || ind.j == nHeight) {
			return true;
		}

		return false;
	}


}