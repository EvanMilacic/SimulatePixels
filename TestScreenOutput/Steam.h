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

		~Steam() {};

		void UpdateState(void) {};
		void UpdatePosition(int index, simulate::Domain* domain) {
			Index_t i = index;
			if (domain->move(i, MoveDirs::Up)) {
				return;
			}
			else if (domain->move(i, MoveDirs::LeftU)) {
				return;
			}
			else if (domain->move(i, MoveDirs::RightU)) {
				return;
			}
			else if (domain->move(i, MoveDirs::Left)) {
				return;
			}
			else if (domain->move(i, MoveDirs::Right)) {
				return;
			}
		};

	private:
		bool directionFlipper = true;

		

	};

} // namespace materie