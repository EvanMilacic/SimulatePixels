#pragma once
#include "Material.h"
namespace materie {

	class Salt : public materie::Material {

	public:

		Salt() {
			type = MatType::Salt;
			color = 0xffffff;
			dynamic = true;
			combustible = false;
			soluble = true;
			hurts = false;
			density = 2000.0f;
			damage = 0.0f;
		};

		~Salt() {};

		void UpdateState(void) {};
		void UpdatePosition(int index, simulate::Domain* domain) {};

	private:


	};

} // namespace materie