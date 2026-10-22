#pragma once
#include "Material.h"
namespace materie{
class Water :
    public Material
{
public:

    Water() {
		type = MatType::Water;
		color = 0x2492e2;
		dynamic = true;
		combustible = false;
		soluble = false;
		hurts = false;
		density = 1000.0f;
		damage = 0.0f;
	};

    ~Water() {};

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

		if (flipDirection() && domain->move(ind, MoveDirs::Left)) {
			return;
		}
		else if (domain->move(ind, MoveDirs::Right)) {
			return;
		}
	};
};

} // namespace materie