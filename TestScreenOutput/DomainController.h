#pragma once
#include <vector>

#include "DomainInterface.h"


class DomainController
{


public:
	DomainController() {};

	~DomainController() {};

private:
	std::vector<DomainInterface> domainsList;

	Index_t iSize;
	Index_t jSize;


};

