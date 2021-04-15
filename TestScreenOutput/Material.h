#pragma once
#include "Domain.h"
#include "Simulator.h"

namespace materie {

	enum class MatType { Default, Sand, Water, Salt, Fire, Wood, Smoke, Steam, Blood };

	class Material
	{
	protected:
		MatType type;
		unsigned int color;
		bool dynamic;
		bool combustible;
		bool soluble;
		bool hurts;

		float density;
		float damage;

	public:
		Material() {
			type = MatType::Default;
			color = 0x000000;
			dynamic = false;
			combustible = false;
			soluble = false;
			hurts = false;
			density = 1.0f;
			damage = 0.0f;
		}

		~Material() {};

		virtual void UpdateState(void) {};
		virtual void UpdatePosition(void) {};
		
		//Getters
		MatType isType(void) { return type; };
		bool isDynamic(void) { return dynamic; };
		bool isCombustible(void) { return combustible; };
		bool isSoluble(void) { return soluble; };
		bool isHurts(void) { return hurts; };
		unsigned int getColor(void) { return color; };
		bool getDensity(void) { return density; };
		bool getDamage(void) { return damage; };
	};


}//namespace materie