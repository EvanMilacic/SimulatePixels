#pragma once
#include "Globals.h"
#include "Domain.h"
#include "Material.h"

namespace materie{

class Sand : public Material{

public:

	Sand() {
		type = MatType::Sand;
		color = 0xe7db45;
		dynamic = true;
		combustible = false;
		soluble = false;
		hurts = false;
		density = 2000.0f;
		damage = 0.0f;
	};

	~Sand() {};

	void UpdateState(void) {};
	void UpdatePosition(int index, simulate::Domain* domain) {
		Index_t i = index;
		if (domain->move(i, MoveDirs::Down)) {
			return;
		}
		else if (domain->move(i, MoveDirs::LeftD)) {
			return;
		}
		else if (domain->move(i, MoveDirs::RightD)) {
			return;
		}

	};

private:


};

} // namespace materie