#pragma once
#include "Sand.h"
namespace materie {

	class Salt : public materie::Sand {

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

	private:


	};

} // namespace materie