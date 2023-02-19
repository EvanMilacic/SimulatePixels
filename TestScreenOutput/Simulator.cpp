#include "Simulator.h"

namespace simulate {

	void Simulator::SimulateDomain(void) {

		moveActiveCells();

		applyPhysics();
	}


	void Simulator::fillActiveMaterialsList(void) {

		activeMaterialsList.clear();

		Index_t nActiveCells = 0;
		for (Index_t n = 0; n < domain.getSize(); n++) {
			if (cellIsActive(n)) {
				activeMaterialsList.push_back(n);
			}
		}
	}

	bool Simulator::cellIsActive(Index_t n) {
		if (domain.isOnEdge(n) && !withEdge) {
			return false;
		}
		else {
			MatType type = domain.at(n);
			materie::Material* material = matFact.getMaterial(type);
			bool isDynamic = material->isDynamic();
			return isDynamic;
		}
	}

	void Simulator::moveActiveCells(void) {
		withEdge = false;
		fillActiveMaterialsList();

		MatType type;
		materie::Material* material;
		Index_t index;
		for (Index_t n = 0; n < activeMaterialsList.size(); n++) {		
			index = activeMaterialsList[n];
			type = domain.at(index);
			material = matFact.getMaterial(type);
			material->UpdatePosition(index, giveGuts());
		}
	}

	void Simulator::applyPhysics(void) {
		withEdge = true;
		fillActiveMaterialsList();

		Index_t index;
		for (Index_t n = 0; n < activeMaterialsList.size(); n++) {
			index = activeMaterialsList[n];
			applyDensity(index);
		}
	}

	void Simulator::applyDensity(Index_t index) {

		Index_t indexUp;
		indexUp = domain.getProjectionIndex(index, MoveDirs::Up);
		if (indexUp < domain.getSize() && evaluateDensity(index, indexUp) ) {
			return;
		}

		Index_t indexLeftUp;
		indexLeftUp = domain.getProjectionIndex(index, MoveDirs::LeftU);
		if (indexLeftUp < domain.getSize() && evaluateDensity(index, indexLeftUp)) {
			return;
		}

		Index_t indexRightUp;
		indexRightUp = domain.getProjectionIndex(index, MoveDirs::RightU);
		if (indexRightUp < domain.getSize() && evaluateDensity(index, indexRightUp)) {
			return;
		}
	}

	bool Simulator::evaluateDensity(Index_t index1, Index_t index2) {
		materie::Material* myMaterial;
		materie::Material* upNeighbour;

		myMaterial = matFact.getMaterial(domain.at(index1));
		upNeighbour = matFact.getMaterial(domain.at(index2));
		float dens_1 = myMaterial->getDensity();
		float dens_2 = upNeighbour->getDensity();

		if (dens_1 < dens_2) {
			domain.flip(index1, index2);
			return true;
		}
		return false;
	}

	unsigned int Simulator::getCellColor(Index_t i, Index_t j) {
		MatType type = domain.at(i, j);
		materie::Material* material = matFact.getMaterial(type);
		unsigned int color = material->getColor();
		return color;
	}


	//Actor functions (act on the simulation
	void Simulator::setCenterSand(void) {
		Index_t i = (Index_t)floor(nWidth * 0.50);
		Index_t j = (Index_t)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Sand);

		i = (Index_t)floor(nWidth * 0.05);
		j = (Index_t)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Sand);

		i = (Index_t)floor(nWidth * 0.25);
		j = (Index_t)floor(nHeight * 0.50);

		domain.set(i, j, MatType::Salt);

		i = (Index_t)floor(nWidth * 0.15);
		j = (Index_t)floor(nHeight * 0.33);

		domain.set(i, j, MatType::Blood);

		i = (Index_t)floor(nWidth * 0.60);
		j = (Index_t)floor(nHeight * 0.33);

		domain.set(i, j, MatType::Water);

		i = (Index_t)floor(nWidth * 0.75);
		j = (Index_t)floor(nHeight * 0.250);

		domain.set(i, j, MatType::Steam);

		i = (Index_t)floor(nWidth * 0.15);
		j = (Index_t)floor(nHeight * 0.750);

		domain.set(i, j, MatType::Smoke);
	}

}  ///namspace simulate