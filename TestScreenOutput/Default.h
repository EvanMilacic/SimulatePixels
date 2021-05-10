#pragma once
#include "Material.h"
namespace materie {

	class Default : public materie::Material {

	public:

		Default() {
			type = MatType::Default;
			color = 0x000000;
			dynamic = false;
			combustible = false;
			soluble = false;
			hurts = false;
			density = -10000.0;
			damage = 0.0f;
		};

		~Default() {};

		void UpdateState(void) {};
		void UpdatePosition(int index, simulate::Domain* domain) {};

	private:


	};

} // namespace materie