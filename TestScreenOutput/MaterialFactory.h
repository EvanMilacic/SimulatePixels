#pragma once

#include "Material.h"
#include "Sand.h"
#include "Blood.h"
#include "Fire.h"
#include "Salt.h"
#include "Smoke.h"
#include "Steam.h"
#include "Water.h"
#include "Wood.h"

namespace materie {

	class MaterialFactory
	{
	public:

		MaterialFactory() {};
		~MaterialFactory() {};


		Material* GetMaterial(MatType type) {
			switch (type) {
			case MatType::Sand: {
				return new Sand();
			}
			case MatType::Water: {
				return new Water();
			}
			case MatType::Salt: {
				return new Salt();
			}
			case MatType::Fire: {
				return new Fire();
			}
			case MatType::Wood: {
				return new Wood();
			}
			case MatType::Smoke: {
				return new Smoke();
			}
			case MatType::Steam: {
				return new Steam();
			}
			case MatType::Blood: {
				return new Blood();
			}
			default: {
				return new Material();
			};
			}
		};

	};

} // namespace materie