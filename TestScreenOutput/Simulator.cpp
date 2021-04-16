#include "Simulator.h"
#include "Material.h"

namespace simulate {

	void Simulator::SimulateDomain(void) {

		fillActiveMaterialsList();

		for (Index_t n = 0; n < activeMaterialsList.size(); n++) {
			MatType type;
			materie::Material* material;
			Index_t index = activeMaterialsList[n];
			type = domain.at(index);
			material = matFact.GetMaterial(type);
			material->UpdatePosition(index, giveGuts());
			delete(material);
		}

		
	}

	bool Simulator::cellIsActive(int n) {
		if (domain.isOnEdge(n)) {
			return false;
		}
		else {
			MatType type = domain.at(n);
			materie::Material* material = matFact.GetMaterial(type);
			bool isDynamic = material->isDynamic();
			delete(material);
			return isDynamic;
		}
	}


	void Simulator::fillActiveMaterialsList(void) {
		
		activeMaterialsList.clear();

		int nActiveCells = 0;
		for (int n = 0; n < domain.getSize(); n++) {
			if (cellIsActive(n)) {
				activeMaterialsList.push_back(n);
				//nActiveCells++;
			}
		}

		//activeMaterialsList.resize(nActiveCells);
		//int counter = 0;
		//for (int n = 0; n < domain.getSize(); n++) {
		//	if (cellIsActive(n)) {
		//		activeMaterialsList[counter] = n;
		//		counter++;
		//	}
		//}
	}

	unsigned int Simulator::getCellColor(int i, int j) {
		MatType type = domain.at(i,j);
		materie::Material* material = matFact.GetMaterial(type);
		unsigned int color = material->getColor();
		delete(material);
		return color;
	}


	//Actor functions (act on the simulation
	void Simulator::setCenterSand(void) {
		int i = (int)floor(nWidth * 0.50);
		int j = (int)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Sand);

		i = (int)floor(nWidth * 0.25);
		j = (int)floor(nHeight * 0.50);

		domain.set(i, j, MatType::Sand);

		i = (int)floor(nWidth * 0.15);
		j = (int)floor(nHeight * 0.33);

		domain.set(i, j, MatType::Sand);

		i = (int)floor(nWidth * 0.75);
		j = (int)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Sand);
	}

}  ///namspace simulate