#include "Domain.h"

namespace simulate {

	bool Domain::move(int index, MoveDirs dir) {

		int* motion = getMotionVector(dir);

		Index_t targetIndex = getDirIndex(index, motion);

		if (isDefault(targetIndex)) {
			MatType temp = field[index];
			field[index] = MatType::Default;
			field[targetIndex] = temp;
		}
		else {
			return false;
		}

	}

	bool Domain::move(int index, MoveDirs dir, int stepLength) {

		Index_t workingIndex, targetIndex;
		workingIndex = index;
		//Get motion vector
		int* motion = getMotionVector(dir);

		//Loop over the length of the vector
		//If an obstructed cell is found, the cell will only be moved until that cell
		for (Index_t n = 0; n < stepLength; n++) {
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

	Index_t Domain::getDirIndex(Index_t index, int* motion) {

		Index2 currentInd = CalcIndex2(index);
		Index2 newInd;

		//Move index along the motion vector
		newInd.i = currentInd.i + motion[0];
		newInd.j = currentInd.j + motion[1];

		//Avoid going out of the domain size
		newInd.i = math::clamp(0, newInd.i, nWidth-1);
		newInd.j = math::clamp(0, newInd.j, nHeight - 1);

		//Convert 2D inex to 1D
		return CalcIndex(newInd);

	}

	int* Domain::getMotionVector(MoveDirs dir) {
		// produces the correct motion vector in the grid
		switch (dir) {
		case MoveDirs::Down: {
			int motion[2] = { 0,1 };
			return motion; }
		case MoveDirs::Up: {
			int motion[2] = { 0,-1 };
			return motion; }
		case MoveDirs::Left: {
			int motion[2] = {-1,0 };
			return motion; }
		case MoveDirs::Right: {
			int motion[2] = {1,0};
			return motion; }
		case MoveDirs::LeftD: {
			int motion[2] = { -1,1 };
			return motion; }
		case MoveDirs::LeftU: {
			int motion[2] = { -1,-1};
			return motion; }
		case MoveDirs::RightD: {
			int motion[2] = { 1,1 };
			return motion; }
		case MoveDirs::RightU: {
			int motion[2] = { 1,-1 };
			return motion; }
		default: {
			int motion[2] = { 0,0 };
			return motion; }
		}

	}

}