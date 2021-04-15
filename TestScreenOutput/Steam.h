#pragma once
#include "Material.h"
namespace materie {

	class Steam : public materie::Material {

	public:

		Steam() {
			type = MatType::Steam;
			color = 0x80a9cc;
			dynamic = true;
			combustible = false;
			soluble = false;
			hurts = true;
			density = -2.0f;
			damage = 5.0f;
		};

		~Steam();

		void UpdateState(void) {};
		void UpdatePosition(void) {};

	private:


	};

} // namespace materie