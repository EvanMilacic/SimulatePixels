#pragma once
#include <vector>

#include "Globals.h"
#include "Defines.h"
#include "Enums.h"
#include "MyMath.h"
#include "Index2.h"
#include "Motion2.h"
#include "Field.h"
#include "FieldData.h"

namespace simulate {

	class Domain
	{
	private:
		FieldData fieldData = { 0,0,0 };
		Field<MatType> field;

		Index2 CalcIndex2(Index2 ind, MoveDirs direction) {
			Motion2 dir = getMotionVector(direction);
			ind += dir;
			return ind;
		}

		bool isDefault(Index2 index) {
			return (field.at(index) == MatType::Default);
		}


	public:
		Domain(FieldData _fieldData) { 
			fieldData = _fieldData;
			field.resize(_fieldData); };
		~Domain() {};


		// Setters
		void setSize(FieldData _fieldData) {
			fieldData = _fieldData;
			field.resize(_fieldData);
		}

		void set(Index2 ind, MatType type) {
			field.set(ind, type);
		}

		void clear(Index2 ind) {
			set(ind, MatType::Default);
		}

		//Getters
		Index_t getSize(void) { return field.size(); };
		Index_t getWidth(void) { return fieldData.Nx; };
		Index_t getHeight(void) { return fieldData.Ny; };

		bool isOnEdge(Index2 ind);
		bool isInBounds(Index2 ind);

		MatType at(Index2 ind) {
			return field.at(ind);
		}

		MatType at(Index2 ind, MoveDirs direction) {
			Index2 index = CalcIndex2(ind,direction);
			return at(index);
		}

		//move operations
		bool move(Index2 ind, MoveDirs dir);
		bool move(Index2 ind, MoveDirs dir, Index_t stepLength);

		void flip(Index2 ind_1, Index2 ind_2) {
			MatType temp = field.at(ind_1);
			field.set(ind_1, field.at(ind_2));
			field.set(ind_2, temp);
		}

		Index2 getProjectionIndex(Index2 ind, MoveDirs direction) {
			Motion2 motion = getMotionVector(direction);
			Index2 targetIndex = getDirIndex(ind, motion);
			return targetIndex;
		}

		private:
		Index2 getDirIndex(Index2 ind, Motion2 motion);
		Motion2 getMotionVector(MoveDirs dir);

	}; //class Domain



}//namespace simulate