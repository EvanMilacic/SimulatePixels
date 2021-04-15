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

	~Sand();

	void UpdateState(void) {};
	void UpdatePosition(int index, simulate::Domain* domain) {
		
	};

private:


};

} // namespace materie