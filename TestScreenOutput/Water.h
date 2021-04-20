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
	void UpdatePosition(int index, simulate::Domain* domain) {
		Index_t i = index;
		if (domain->move(i, MoveDirs::Down)) {
			return;
		}
		
		if (flipDirection() && domain->move(i, MoveDirs::LeftD)) {
			return;
		}
		else if (domain->move(i, MoveDirs::RightD)) {
			return;
		}

		if (flipDirection() && domain->move(i, MoveDirs::Left)) {
			return;
		}
		else if (domain->move(i, MoveDirs::Right)) {
			return;
		}
	};
};

} // namespace materie