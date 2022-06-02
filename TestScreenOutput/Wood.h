#pragma once
#include "Material.h"
namespace materie {

	class Wood : public materie::Material {

	public:

		Wood() {
			type = MatType::Wood;
			color = 0x9d612d;
			dynamic = true;
			combustible = true;
			soluble = false;
			hurts = false;
			density = 800.0f;
			damage = 0.0f;
		};

		~Wood() {};

		void UpdateState(void) {};
		void UpdatePosition(int index, simulate::BaseDomain* domain) {};

	private:


	};

} // namespace materie