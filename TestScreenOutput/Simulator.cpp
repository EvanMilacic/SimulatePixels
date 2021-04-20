#include "Simulator.h"

namespace simulate {

	void Simulator::SimulateDomain(void) {

		fillActiveMaterialsList();

		for (Index_t n = 0; n < activeMaterialsList.size(); n++) {
			MatType type;
			materie::Material* material;
			Index_t index = activeMaterialsList[n];
			type = domain.at(index);
			material = matFact.getMaterial(type);
			material->UpdatePosition(index, giveGuts());
		}


	}

	bool Simulator::cellIsActive(int n) {
		if (domain.isOnEdge(n)) {
			return false;
		}
		else {
			MatType type = domain.at(n);
			materie::Material* material = matFact.getMaterial(type);
			bool isDynamic = material->isDynamic();
			return isDynamic;
		}
	}


	void Simulator::fillActiveMaterialsList(void) {

		activeMaterialsList.clear();

		int nActiveCells = 0;
		for (int n = 0; n < domain.getSize(); n++) {
			if (cellIsActive(n)) {
				activeMaterialsList.push_back(n);
			}
		}
	}

	unsigned int Simulator::getCellColor(int i, int j) {
		MatType type = domain.at(i, j);
		materie::Material* material = matFact.getMaterial(type);
		unsigned int color = material->getColor();
		return color;
	}


	//Actor functions (act on the simulation
	void Simulator::setCenterSand(void) {
		int i = (int)floor(nWidth * 0.50);
		int j = (int)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Sand);

		i = (int)floor(nWidth * 0.05);
		j = (int)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Sand);

		i = (int)floor(nWidth * 0.25);
		j = (int)floor(nHeight * 0.50);

		domain.set(i, j, MatType::Salt);

		i = (int)floor(nWidth * 0.15);
		j = (int)floor(nHeight * 0.33);

		domain.set(i, j, MatType::Blood);

		i = (int)floor(nWidth * 0.60);
		j = (int)floor(nHeight * 0.33);

		domain.set(i, j, MatType::Water);

		i = (int)floor(nWidth * 0.75);
		j = (int)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Steam);

		i = (int)floor(nWidth * 0.15);
		j = (int)floor(nHeight * 0.750);

		domain.set(i, j, MatType::Smoke);
	}

}  ///namspace simulate