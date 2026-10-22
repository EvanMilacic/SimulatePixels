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
		void setSize(int width, int height) {
			nWidth = width;
			nHeight = height;
			nSize = nWidth * nHeight;
		};

		void set(Index_t index, MatType type) { field->set(index, type); };
		void set(int i, int j, MatType type) { field->set(i, j, type); };
		void set(Index2 ind, MatType type) { field->set(ind, type); };

		void clear(Index_t index) { field->clear(index); };
		void clear(Index2 ind) { field->clear(ind); };

		//Getters
		int getSize(void) { return field->getSize(); };
		int getWidth(void) { return nWidth; };
		int getHeight(void) { return nHeight; };

		MatType at(int index) { return field->at(index); };
		MatType at(int i, int j) { return field->at(i, j); };
		MatType at(Index2 ind) { return field->at(ind); };
		MatType at(Index2 ind, MoveDirs direction) { return field->at(ind, LUT_MV.get(direction)); };

		Index_t CalcIndex(int i, int j) { return field->CalcIndex(i, j); };
		Index_t CalcIndex(Index2 ind) { return field->CalcIndex(ind); };

		void flip(int index_1, int index_2) { field->flip(index_1, index_2); };
		void flip(Index2 ind_1, Index2 ind_2) { field->flip(ind_1, ind_2); };

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