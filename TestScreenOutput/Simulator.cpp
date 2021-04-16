#include "Simulator.h"
#include "Material.h"

namespace simulate {

	void Simulator::SimulateDomain(void) {

		fillActiveMaterialsList();

		for (int n = 0; n < activeMaterialsList.size(); n++) {

		}

	}

	bool Simulator::cellIsActive(int n) {
		materie::MatType type = domain.at(n);
		materie::Material* material = matFact.GetMaterial(type);
		return material->isDynamic();
	}


	void Simulator::fillActiveMaterialsList(void) {
		
		activeMaterialsList.clear();

		int nActiveCells = 0;
		for (int n = 0; n < domain.getSize(); n++) {
			if (cellIsActive(n)) {
				nActiveCells++;
			}
		}

		activeMaterialsList.resize(nActiveCells);

		for (int n = 0; n < domain.getSize(); n++) {
			if (cellIsActive(n)) {
				activeMaterialsList.push_back(n);
			}
		}
	}

	unsigned int Simulator::getCellColor(int i, int j) {
		materie::MatType type = domain.at(i,j);
		materie::Material* material = matFact.GetMaterial(type);
		return material->getColor();
	}


	//Actor functions (act on the simulation
	void Simulator::setCenterSand(void) {
		int i = floor(nWidth * 0.50);
		int j = floor(nHeight * 0.60);

		domain.set(i, j, materie::MatType::Sand);
	}

}  ///namspace simulate