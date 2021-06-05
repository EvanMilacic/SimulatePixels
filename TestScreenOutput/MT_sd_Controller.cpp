#include "MT_sd_Controller.h"

namespace multi_t {

	void MT_sd_Controller::divideField(void) {
		int fWidth = fController->getNumWidth();
		int fHeight = fController->getNumHeight();

		double nBoxesWide = fWidth / iSize;
		double nBoxesHigh = fHeight / jSize;

		NIsubs = (int)ceil(nBoxesWide);
		NJsubs = (int)ceil(nBoxesHigh);

		nSubs = NIsubs * NJsubs;

		domainsList.resize(nSubs);

		int StartI, StartJ;
		int y, x;
		int xBoxSize, yBoxSize;
		int tag;

		for (int n = 0; n < nSubs; n++) {

			y = (int)floor(n / nBoxesWide);
			x = n - y;

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


	void MT_sd_Controller::multiThreadTesting(int nThreads) {

#pragma omp parallel for
		for (int n = 0; n < nSubs; n += 4) {
			if (domainsList[n].tag == 1) {
				domainsList[n].DoSomethig();
			}
		}

#pragma omp parallel for
		for (int n = 1; n < nSubs; n += 4) {
			if (domainsList[n].tag == 2) {
				domainsList[n].DoSomethig();
			}
		}

#pragma omp parallel for
		for (int n = 2; n < nSubs; n += 4) {
			if (domainsList[n].tag == 3) {
				domainsList[n].DoSomethig();
			}
		}

#pragma omp parallel for
		for (int n = 3; n < nSubs; n += 4) {
			if (domainsList[n].tag == 4) {
				domainsList[n].DoSomethig();
			}
		}


	}

} //namespace