#include "Domain.h"

namespace simulate {

	bool Domain::move(Index2 ind, MoveDirs dir) {
		//Get Motion vector
		Motion2 motion = getMotionVector(dir);
		//Calculate the target cell
		Index2 targetIndex = getDirIndex(ind, motion);
		//If cell is not occupied, move there
		if (isDefault(targetIndex)) {
			flip(ind, targetIndex);
			return true;
		}
		else {
			return false;
		}

	}

	bool Domain::move(Index2 ind, MoveDirs dir, Index_t stepLength) {

		Index2 workingIndex, targetIndex;
		workingIndex = ind;
		targetIndex = ind;
		//Get motion vector
		Motion2 motion = getMotionVector(dir);

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
		MatType temp = field.at(ind);
		field.set(ind, MatType::Default);
		field.set(targetIndex, temp);
		//Provide succes boolean
		return true;
	}

	Index2 Domain::getDirIndex(Index2 ind, Motion2 motion) {

		Index2 currentInd = ind;
		Index2 newInd;

		//Move index along the motion vector
		newInd.i = currentInd.i + motion.i;
		newInd.j = currentInd.j + motion.j;

		//Avoid going out of the domain size
		newInd.i = math::clamp(0, newInd.i, fieldData.Nx - 1);
		newInd.j = math::clamp(0, newInd.j, fieldData.Ny - 1);

		//Convert 2D inex to 1D
		return newInd;

	}

	Motion2 Domain::getMotionVector(MoveDirs dir) {
		// produces the correct motion vector in the grid
		switch (dir) {
		case MoveDirs::Down: {
			Motion2 motion = { 0,-1 };
			return motion; }
		case MoveDirs::Up: {
			Motion2 motion = { 0,1 };
			return motion; }
		case MoveDirs::Left: {
			Motion2 motion = {-1,0 };
			return motion; }
		case MoveDirs::Right: {
			Motion2 motion = {1,0};
			return motion; }
		case MoveDirs::LeftD: {
			Motion2 motion = { -1,-1 };
			return motion; }
		case MoveDirs::LeftU: {
			Motion2 motion = { -1,1};
			return motion; }
		case MoveDirs::RightD: {
			Motion2 motion = { 1,-1 };
			return motion; }
		case MoveDirs::RightU: {
			Motion2 motion = { 1,1 };
			return motion; }
		default: {
			Motion2 motion = { 0,0 };
			return motion; }
		}
	}

	bool Domain::isOnEdge(Index2 ind){
		if (ind.i == 0 || ind.i == fieldData.Nx-1) {
			return true;
		}
		if (ind.j == 0 || ind.j == fieldData.Ny-1) {
			return true;
		}
		return false;
	}

	bool Domain::isInBounds(Index2 ind) {
		if (0 <= ind.i && ind.i <= fieldData.Nx - 1
			&& 0 <= ind.j && ind.j <= fieldData.Ny - 1) {
			return true;
		}
		return false;
	}
}