#pragma once
#include <vector>

#include "Structs.h"
#include "Field.h"
#include "Domain.h"
#include "Enums.h"
#include "MaterialFactory.h"

namespace simulate {
class Simulator
{
private:
	int nWidth;
	int nHeight;
	bool withEdge = false;
	std::vector<int> activeMaterialsList;

	Field field;
	BaseDomain domain;
	
	materie::MaterialFactory matFact;

	bool cellIsActive(int n);
	void fillActiveMaterialsList(void);
	void moveActiveCells(void);
	void applyPhysics(void);
	void applyDensity(Index_t index);
	bool evaluateDensity(Index_t index1, Index_t index2);
public:
	Simulator(RenderState renderState) : field(10,10), domain(10, 10, &field){
		setSize(renderState);
	}
	Simulator(int width, int height): field(10,10), domain(10, 10, &field) {
		setSize(width, height);
	};
	~Simulator() {};


	void SimulateDomain(void);
	void simulateCellAt(Index_t index);


	//Getters
	int getNumWidth() { return nWidth; };
	int getNumHeight() { return nHeight; };
	int getNumSize() { return nWidth * nHeight; };

	MatType getCellMaterial(int i, int j) { return domain.at(i, j); };
	unsigned int getCellColor(int i, int j);

	BaseDomain* giveGuts(void) {
		return &domain;
	}

	//Setters
	void setSize(RenderState renderState) {
		setSize(renderState.width,renderState.height);
	};
	void setSize(int width, int height) {
		nWidth = width;
		nHeight = height;
		field.setSize(width, height);
		domain.setSize(width, height);
	};

	//Actors
	void setCenterSand(void);
};

} // namespace simulate