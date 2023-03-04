#pragma once
#include <vector>
#include <iostream>

#include "Index2.h"
#include "Domain.h"
#include "Enums.h"
#include "MaterialFactory.h"

namespace simulate {
class Simulator
{
private:
	FieldData fieldData = { 10,10,100 };
	bool withEdge = false;
	std::vector<Index2> activeMaterialsList;

	Domain domain;
	
	materie::MaterialFactory matFact;

	bool cellIsActive(Index2 ind);
	void fillActiveMaterialsList(void);
	void moveActiveCells(void);
	void applyPhysics(void);
	void applyDensity(Index2 ind);
	bool evaluateDensity(Index2 ind_1, Index2 ind_2);
public:
	Simulator(RenderState renderState) : domain({10,10,100}) {
		setSize(renderState);
	}
	Simulator(FieldData fData) : domain({ 10,10,100 }) {
		setSize(fData);
	};
	~Simulator() {};


	void SimulateDomain(void);


	//Getters
	Index_t getNumWidth() { return fieldData.Nx; };
	Index_t getNumHeight() { return fieldData.Ny; };
	Index_t getNumSize() { return fieldData.Size; };

	MatType getCellMaterial(Index2 ind) { return domain.at(ind); };
	Index_t getCellColor(Index2 ind);

	Domain* giveGuts(void) {
		return &domain;
	}

	//Setters
	void setSize(RenderState renderState) {
		FieldData fData = { 
			static_cast<Index_t>(renderState.width), 
			static_cast<Index_t>(renderState.height), 
			static_cast<Index_t>(renderState.width*renderState.height) };
		setSize(fData);
	};
	void setSize(FieldData fData) {
		fieldData = fData;
		domain.setSize(fData);
	};

	//Actors
	void setCenterSand(void);
};

} // namespace simulate