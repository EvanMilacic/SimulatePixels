#pragma once
#include "Material.h"
namespace materie {

	class Fire : public materie::Material {

	public:

		Fire() {
			type = MatType::Fire;
			color = 0xf2db1b;
			dynamic = true;
			combustible = false;
			soluble = false;
			hurts = true;
			density = 1.0f;
			damage = 10.0f;
		};

		~Fire() {};

		void UpdateState(void) {};
		void UpdatePosition(int index, simulate::Domain* domain) {};

	private:


	};

} // namespace materie