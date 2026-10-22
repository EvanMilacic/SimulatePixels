#include "MT_subDomain.h"

namespace multi_t {

	// Simulates every cell that falls inside this box's region of the field.
	// Bounds are clamped against the simulator's actual size since the last
	// row/column of boxes can be smaller than iSize/jSize (see
	// MT_sd_Controller::divideField).
	void MT_subDomain::simulateSubDomain(void) {
		if (simulator == nullptr) {
			return;
		}

		simulate::BaseDomain* domain = simulator->giveGuts();

		int iEnd = iStart + width;
		if (iEnd > simulator->getNumWidth()) {
			iEnd = simulator->getNumWidth();
		}

		int jEnd = jStart + height;
		if (jEnd > simulator->getNumHeight()) {
			jEnd = simulator->getNumHeight();
		}

		for (int j = jStart; j < jEnd; j++) {
			for (int i = iStart; i < iEnd; i++) {
				Index_t index = domain->CalcIndex(i, j);
				simulator->simulateCellAt(index);
			}
		}
	}


};