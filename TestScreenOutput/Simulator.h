#pragma once
#include <vector>

#include "Index2.h"
#include "Domain.h"
#include "Enums.h"
#include "MaterialFactory.h"

namespace simulate {
class Simulator
{
private:
	Index_t nWidth;
	Index_t nHeight;
	bool withEdge = false;
	std::vector<Index_t> activeMaterialsList;

	Domain domain;
	
	materie::MaterialFactory matFact;

	bool cellIsActive(Index_t n);
	void fillActiveMaterialsList(void);
	void moveActiveCells(void);
	void applyPhysics(void);
	void applyDensity(Index_t index);
	bool evaluateDensity(Index_t index1, Index_t index2);
public:
	Simulator(RenderState renderState) : domain(10,10){
		setSize(renderState);
	}
	Simulator(Index_t width, Index_t height): domain(10,10) {
		setSize(width, height);
	};
	~Simulator() {};


	void SimulateDomain(void);


	//Getters
	Index_t getNumWidth() { return nWidth; };
	Index_t getNumHeight() { return nHeight; };
	Index_t getNumSize() { return nWidth * nHeight; };

	MatType getCellMaterial(Index_t i, Index_t j) { return domain.at(i, j); };
	Index_t getCellColor(Index_t i, Index_t j);

	Domain* giveGuts(void) {
		return &domain;
	}

	//Setters
	void setSize(RenderState renderState) {
		setSize(renderState.width,renderState.height);
	};
	void setSize(Index_t width, Index_t height) {
		nWidth = width;
		nHeight = height;
		domain.setSize(width, height);
	};

	//Actors
	void setCenterSand(void);
};

} // namespace simulate