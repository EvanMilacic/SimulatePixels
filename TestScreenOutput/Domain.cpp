#include "Domain.h"

namespace simulate {
	bool Domain::move(Index2 ind, MoveDirs dir)
	{
		int index = field.CalcIndex(ind);
		return move(index, dir);
	}
	bool Domain::move(int index, MoveDirs dir) {
		//Get Motion vector
		Index2 motion = LUT_MV.get(dir);
		//Calculate the target cell
		Index_t targetIndex = getDirIndex(index, motion);
		//If cell is not occupied, move there
		if (isDefault(targetIndex)) {
			field.flip(index, targetIndex);
			return true;
		}
		else {
			return false;
		}

	}

	bool Domain::move(int index, MoveDirs dir, int stepLength) {

		Index_t workingIndex, targetIndex;
		workingIndex = index;
		targetIndex = index;
		//Get motion vector
		Index2 motion = LUT_MV.get(dir);

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
		MatType temp = field.at(index);
		field.clear(index);
		field.set(targetIndex,temp);
		//Provide succes boolean
		return true;
	}

	Index_t Domain::getDirIndex(Index_t index, Index2 motion) {

		Index2 currentInd = field.CalcIndex2(index);
		Index2 newInd;

		//Move index along the motion vector
		newInd.i = currentInd.i + motion.i;
		newInd.j = currentInd.j + motion.j;

		//Avoid going out of the domain size
		newInd.i = math::clamp(0, newInd.i, nWidth-1);
		newInd.j = math::clamp(0, newInd.j, nHeight - 1);

		//Convert 2D inex to 1D
		return field.CalcIndex(newInd);

	}

	bool Domain::isOnEdge(Index_t index) {
		Index2 ind = field.CalcIndex2(index);
		return isOnEdge(ind);
	}

	bool Domain::isOnEdge(Index2 ind){
		if (ind.i == 0 || ind.i == nWidth-1) {
			return true;
		}
		if (ind.j == 0 || ind.j == nHeight-1) {
			return true;
		}

		return false;
	}

}