#pragma once
#include "Water.h"

namespace materie {

	class Blood : public materie::Water {

	public:

		Blood() {
			type = MatType::Blood;
			color = 0xc40808;
			dynamic = true;
			combustible = false;
			soluble = true;
			hurts = false;
			density = 1500.0f;
			damage = 0.0f;
		};

		~Blood() {};

		void UpdateState(void) {};

	private:


	};

} // namespace materie