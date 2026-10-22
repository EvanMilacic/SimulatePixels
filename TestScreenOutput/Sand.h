#pragma once
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
	void UpdatePosition(Index2 ind, simulate::Domain* domain) {
		if (domain->move(ind, MoveDirs::Down)) {
			return;
		}

		if (flipDirection() && domain->move(ind, MoveDirs::LeftD)) {
			return;
		}
		else if (domain->move(ind, MoveDirs::RightD)) {
			return;
		}

	};

private:


};

} // namespace materie