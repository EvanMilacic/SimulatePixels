#pragma once
#include <vector>

#include "Structs.h"
#include "Domain.h"
#include "Material.h"
#include "MaterialFactory.h"

namespace simulate {
class Simulator
{
private:
	int nWidth;
	int nHeight;

	std::vector<int> activeMaterialsList;

	Domain domain;
	
	materie::MaterialFactory matFact;

	bool cellIsActive(int n);
	void fillActiveMaterialsList(void);

public:
	Simulator() {};
	Simulator(RenderState renderState){
		setSize(renderState);
	}
	Simulator(int width, int height) {
		domain.setSize(width, height);
	};
	~Simulator() {};


	void SimulateDomain(void);


	//Getters
	int getNumWidth() { return nWidth; };
	int getNumHeight() { return nHeight; };
	int getNumSize() { return nWidth * nHeight; };

	materie::MatType getCellMaterial(int i, int j) { return domain.at(i,j); };
	unsigned int getCellColor(int i, int j);

	Domain* giveGuts(void) {
		return &domain;
	}

	//Setters
	void setSize(RenderState renderState) {
		setSize(renderState.width,renderState.height);
	};
	void setSize(int width, int height) {
		nWidth = width;
		nHeight = height;
		domain.setSize(width, height);
	};

};

} // namespace simulate