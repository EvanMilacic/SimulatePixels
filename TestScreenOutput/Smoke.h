#pragma once
#include "Material.h"
namespace materie {

	class Smoke : public materie::Material {

	public:

		Smoke() {
			type = MatType::Smoke;
			color = 0x8596a4;
			dynamic = true;
			combustible = false;
			soluble = false;
			hurts = true;
			density = -1.0f;
			damage = 0.0f;
		};

		~Smoke();

		void UpdateState(void) {};
		void UpdatePosition(void) {};

	private:


	};

} // namespace materie