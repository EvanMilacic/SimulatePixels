#pragma once
#include "Material.h"
namespace materie {

	class Blood : public materie::Material {

	public:

		Blood() {
			type = MatType::Blood;
			color = 0x8596a4;
			dynamic = true;
			combustible = false;
			soluble = true;
			hurts = false;
			density = 1500.0f;
			damage = 0.0f;
		};

		~Blood();

		void UpdateState(void) {};
		void UpdatePosition(void) {};

	private:


	};

} // namespace materie