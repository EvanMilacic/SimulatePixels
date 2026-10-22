#include "MT_sd_Controller.h"
#include <cmath>

namespace multi_t {

	void MT_sd_Controller::divideField(void) {
		int fWidth = fController->getNumWidth();
		int fHeight = fController->getNumHeight();

		double nBoxesWide = static_cast<double>(fWidth) / iSize;
		double nBoxesHigh = static_cast<double>(fHeight) / jSize;

		NIsubs = (int)ceil(nBoxesWide);
		NJsubs = (int)ceil(nBoxesHigh);

		nSubs = NIsubs * NJsubs;

		domainsList.resize(nSubs);

		int StartI, StartJ;
		int y, x;
		int xBoxSize, yBoxSize;
		int tag;

		for (int n = 0; n < nSubs; n++) {

			y = n / NIsubs;
			x = n % NIsubs;

			StartI = x * iSize;
			StartJ = y * jSize;

			if (StartI + iSize < fWidth) {
				xBoxSize = StartI + iSize;
			}
			else {
				xBoxSize = fWidth - StartI;
			}

			if (StartJ + jSize < fHeight) {
				yBoxSize = StartJ + jSize;
			}
			else {
				yBoxSize = fHeight - StartJ;
			}

			if (x % 2 == 0 || x == 0) {
				tag = 1;
			}
			else {
				tag = 2;
			}

			if (y % 2 == 0 || y == 0) {
			}
			else {
				tag += 2;
			}

			domainsList[n] = MT_subDomain(fController, tag, iSize, jSize, StartI, StartJ);
		}
	}


	void MT_sd_Controller::multiThread(int nThreads) {

		// Red-black (4-colour) checkerboard scheme: boxes carrying the same
		// tag never touch each other (tags are assigned from (x%2, y%2) in
		// divideField()), so every colour's pass can run in parallel without
		// adjacent boxes racing on shared border cells. Iterating with a
		// fixed stride of 4 over the flat domainsList only lines up with the
		// tags when NIsubs is even, so instead we scan every box per pass and
		// just skip the ones that don't match the current colour.
		for (int tag = 1; tag <= 4; tag++) {
#pragma omp parallel for num_threads(nThreads)
			for (int n = 0; n < nSubs; n++) {
				if (domainsList[n].tag == tag) {
					domainsList[n].simulateSubDomain();
				}
			}
		}

	}

} //namespace