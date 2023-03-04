#include "Simulator.h"

namespace simulate {

	void Simulator::SimulateDomain(void) {

		moveActiveCells();

		applyPhysics();
	}


	void Simulator::fillActiveMaterialsList(void) {

		activeMaterialsList.clear();

		Index_t nActiveCells = 0;
		for (Index_t _width = 0; _width < domain.getWidth(); _width++) {
			for (Index_t _height = 0; _height < domain.getHeight(); _height++){
				if (cellIsActive({ _width, _height })) {
					activeMaterialsList.push_back({ _width, _height });
					nActiveCells += 1;
				}
			}
		}
		std::cout << "Number of active materials = " << nActiveCells << std::endl;
	}

	bool Simulator::cellIsActive(Index2 ind) {
		if (domain.isOnEdge(ind) && !withEdge) {
			return false;
		}
		else {
			MatType type = domain.at(ind);
			materie::Material* material = matFact.getMaterial(type);
			if (type != MatType::Default) {
				std::cout << "We have water" << std::endl;
			}
			bool isDynamic = material->isDynamic();
			if (isDynamic) {
				std::cout << "Material is dynamic" << std::endl;
			}
			return isDynamic;
		}
	}

	void Simulator::moveActiveCells(void) {
		withEdge = false;
		fillActiveMaterialsList();

		MatType type;
		materie::Material* material;
		Index2 ind;
		for (Index_t n = 0; n < activeMaterialsList.size(); n++) {		
			ind = activeMaterialsList[n];
			type = domain.at(ind);
			material = matFact.getMaterial(type);
			material->UpdatePosition(ind, giveGuts());
		}
	}

	void Simulator::applyPhysics(void) {
		withEdge = true;
		fillActiveMaterialsList();

		Index2 ind;
		for (Index_t n = 0; n < activeMaterialsList.size(); n++) {
			ind = activeMaterialsList[n];
			applyDensity(ind);
		}
	}

	void Simulator::applyDensity(Index2 ind) {

		Index2 indUp;
		indUp = domain.getProjectionIndex(ind, MoveDirs::Up);
		if (domain.isInBounds(indUp) && evaluateDensity(ind, indUp)) {
			return;
		}

		Index2 indLeftUp;
		indLeftUp = domain.getProjectionIndex(ind, MoveDirs::LeftU);
		if (domain.isInBounds(indLeftUp) && evaluateDensity(ind, indLeftUp)) {
			return;
		}

		Index2 indRightUp;
		indRightUp = domain.getProjectionIndex(ind, MoveDirs::RightU);
		if (domain.isInBounds(indRightUp) && evaluateDensity(ind, indRightUp)) {
			return;
		}
	}

	bool Simulator::evaluateDensity(Index2 ind_1, Index2 ind_2) {
		materie::Material* myMaterial;
		materie::Material* upNeighbour;

		myMaterial = matFact.getMaterial(domain.at(ind_1));
		upNeighbour = matFact.getMaterial(domain.at(ind_2));
		float dens_1 = myMaterial->getDensity();
		float dens_2 = upNeighbour->getDensity();

		if (dens_1 < dens_2) {
			domain.flip(ind_1, ind_2);
			return true;
		}
		return false;
	}

	unsigned int Simulator::getCellColor(Index2 ind) {
		MatType type = domain.at(ind);
		materie::Material* material = matFact.getMaterial(type);
		unsigned int color = material->getColor();
		return color;
	}


	//Actor functions (act on the simulation
	void Simulator::setCenterSand(void) {
		Index_t i = (Index_t)floor(fieldData.Nx * 0.50);
		Index_t j = (Index_t)floor(fieldData.Ny * 0.250);

		domain.set({ i, j }, MatType::Sand);

		i = (Index_t)floor(fieldData.Nx * 0.05);
		j = (Index_t)floor(fieldData.Ny * 0.250);

		domain.set({ i, j }, MatType::Sand);

		i = (Index_t)floor(fieldData.Nx * 0.25);
		j = (Index_t)floor(fieldData.Ny * 0.50);

		domain.set({ i, j }, MatType::Salt);

		i = (Index_t)floor(fieldData.Nx * 0.15);
		j = (Index_t)floor(fieldData.Ny * 0.33);

		domain.set({ i, j }, MatType::Blood);

		i = (Index_t)floor(fieldData.Nx * 0.60);
		j = (Index_t)floor(fieldData.Ny * 0.33);

		domain.set({ i, j }, MatType::Water);

		i = (Index_t)floor(fieldData.Nx * 0.75);
		j = (Index_t)floor(fieldData.Ny * 0.250);

		domain.set({ i, j }, MatType::Steam);

		i = (Index_t)floor(fieldData.Nx * 0.15);
		j = (Index_t)floor(fieldData.Ny * 0.750);

		domain.set({ i, j }, MatType::Smoke);
	}

}  ///namspace simulate