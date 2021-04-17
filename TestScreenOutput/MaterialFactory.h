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
#include "Default.h"

namespace materie {

	class MaterialFactory
	{
	public:

		MaterialFactory() {};
		~MaterialFactory() {};

	private:
		Sand _sand;
		Water _water;
		Salt _salt;
		Fire _fire;
		Wood _wood;
		Smoke _smoke;
		Steam _steam;
		Blood _blood;
		Default _default;

	public:

		Material* getMaterial(MatType type) {
			switch (type) {
			case MatType::Sand: {
				return &_sand;
			}
			case MatType::Water: {
				return &_water;
			}
			case MatType::Salt: {
				return &_salt;
			}
			case MatType::Fire: {
				return &_fire;
			}
			case MatType::Wood: {
				return &_wood;
			}
			case MatType::Smoke: {
				return &_smoke;
			}
			case MatType::Steam: {
				return &_steam;
			}
			case MatType::Blood: {
				return &_blood;
			}
			case MatType::Default: {
				return &_default;
			}
			default: {
				return &_default;
			};
			}
		}

	};

} // namespace materie