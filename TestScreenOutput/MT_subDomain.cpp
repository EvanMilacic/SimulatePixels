#include "MT_subDomain.h"

namespace multi_t {

	// Simulates every cell that falls inside this box's region of the field.
	// Bounds are clamped against the simulator's actual size since the last
	// row/column of boxes can be smaller than iSize/jSize (see
	// MT_sd_Controller::divideField). Cells are addressed directly via
	// Index2 - Domain no longer exposes a linear CalcIndex().
	void MT_subDomain::simulateSubDomain(void) {
		if (simulator == nullptr) {
			return;
		}

		int iEnd = iStart + width;
		if (iEnd > static_cast<int>(simulator->getNumWidth())) {
			iEnd = static_cast<int>(simulator->getNumWidth());
		}

		int jEnd = jStart + height;
		if (jEnd > static_cast<int>(simulator->getNumHeight())) {
			jEnd = static_cast<int>(simulator->getNumHeight());
		}

		for (int j = jStart; j < jEnd; j++) {
			for (int i = iStart; i < iEnd; i++) {
				simulator->simulateCellAt({ static_cast<Index_t>(i), static_cast<Index_t>(j) });
			}
		}
	}


};