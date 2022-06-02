#pragma once
#include <vector>

#include "Globals.h"
#include "Enums.h"
#include "MyMath.h"
#include "FieldController.h"

namespace simulate {

	class BaseDomain
	{
	private:
		int nWidth;
		int nHeight;
		int nSize;

		FieldController *field;
		LUT_MotionVector LUT_MV;

		bool isDefault(Index_t index) {
			return (field->at(index) == MatType::Default);
		}

	public:
		BaseDomain(int width, int height, Field *_field) { 
			field = new FieldController(_field);
			setSize(width, height); 
		};
		~BaseDomain() {
			delete(field);
		};

		// Setters

		//Getters
		int getSize(void) { return field->getSize(); };
		int getWidth(void) { return nWidth; };
		int getHeight(void) { return nHeight; };

		bool isOnEdge(Index_t index);
		bool isOnEdge(Index2 ind);

		//move operations
		bool move(Index2 ind, MoveDirs dir);
		bool move(int index, MoveDirs dir);
		bool move(int index, MoveDirs dir, int stepLength);

		Index_t getProjectionIndex(Index_t index, MoveDirs direction) {
			Index2 motion = LUT_MV.get(direction);
			Index_t targetIndex = getDirIndex(index, motion);
			return targetIndex;
		}

		private:
		Index_t getDirIndex(Index_t index, Index2 motion);

	}; //class Domain



}//namespace simulate