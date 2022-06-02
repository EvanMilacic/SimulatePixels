#include "DomainInterface.h"

bool DomainInterface::move(Index2 ind, MoveDirs dir)
{
	int index = field->CalcIndex(ind);
	return move(index, dir);
}
bool DomainInterface::move(Index_t index, MoveDirs dir) {
	//Get Motion vector
	Index2 motion = motionVector.get(dir);
	//Calculate the target cell
	Index_t targetIndex = getDirIndex(index, motion);
	//If cell is not occupied, move there
	if (field->isDefault(targetIndex)) {
		field->flip(index, targetIndex);
		return true;
	}
	else {
		return false;
	}
}

bool DomainInterface::move(Index_t index, MoveDirs dir, Index_t stepLength) {

	Index_t workingIndex, targetIndex;
	workingIndex = index;
	targetIndex = index;
	//Get motion vector
	Index2 motion = motionVector.get(dir);

	//Loop over the length of the vector
	//If an obstructed cell is found, the cell will only be moved until that cell
	for (int n = 0; n < stepLength; n++) {
		//Get target cell id
		targetIndex = getDirIndex(workingIndex, motion);
		//Check if it is empty
		if (field->isDefault(targetIndex)) {
			//If empty, prepare for next step
			workingIndex = targetIndex;
		}
		else if (!field->isDefault(targetIndex) && n > 0) {
			//If vector obstructed
			break;
		}
		else {
			//If cell occupied
			return false;
		}
	}

	//Move cell to target location
	MatType temp = field->at(index);
	field->clear(index);
	field->set(targetIndex, temp);
	//Provide succes boolean
	return true;
}


Index_t DomainInterface::getDirIndex(Index_t index, Index2 motion) {

	Index2 currentInd = field->CalcIndex2(index);
	Index2 newInd;

	//Move index along the motion vector
	newInd.i = currentInd.i + motion.i;
	newInd.j = currentInd.j + motion.j;

	//Avoid going out of the domain size
	newInd.i = math::clamp(0, newInd.i, width - 1);
	newInd.j = math::clamp(0, newInd.j, height - 1);

	//Convert 2D inex to 1D
	return field->CalcIndex(newInd);

}

bool DomainInterface::isOnEdge(Index_t index) {
	Index2 ind = field->CalcIndex2(index);
	return isOnEdge(ind);
}

bool DomainInterface::isOnEdge(Index2 ind) {
	if (ind.i == 0 || ind.i == width - 1) {
		return true;
	}
	if (ind.j == 0 || ind.j == height - 1) {
		return true;
	}

	return false;
}