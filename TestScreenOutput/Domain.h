#pragma once
#include <vector>

#include "Globals.h"
#include "Enums.h"
#include "MyMath.h"
#include "Field.h"

namespace simulate {

	class Domain
	{
	private:
		int nWidth;
		int nHeight;
		int nSize;

		Field field;
		LUT_MotionVector LUT_MV;

		bool isDefault(Index_t index) {
			return (field.at(index) == MatType::Default);
		}

	public:
		Domain(int width, int height) { setSize(width, height); };
		~Domain() {};

		// Setters
		void set(int width, int height, MatType type) {
			field.set(width, height, type);
		}

		void set(Index2 ind, MatType type) {
			field.set(ind, type);
		}

		void set(int index, MatType type) {
			field.set(index,type);
		}

		void setSize(int width, int height) {
			nWidth = width;
			nHeight = height;
			field.setSize(width, height);
		}

		//Getters
		MatType at(int index) { return field.at(index); };
		MatType at(Index2 ind) { return field.at(ind); };
		MatType at(int width, int height) { return field.at(width, height); };
		MatType at(Index2 ind, MoveDirs direction) { 
			Index2 motionVector = LUT_MV.get(direction);
			return field.at(ind, motionVector); };
		MatType at(int index, MoveDirs direction) { 
			Index2 motionVector = LUT_MV.get(direction);
			return field.at(index, motionVector); };
		MatType at(Index2 ind, Index2 motionVector) { return field.at(ind, motionVector); };
		MatType at(int index, Index2 motionVector) { return field.at(index, motionVector); };

		int getSize(void) { return field.getSize(); };
		int getWidth(void) { return nWidth; };
		int getHeight(void) { return nHeight; };

		bool isOnEdge(Index_t index);
		bool isOnEdge(Index2 ind);

		//move operations
		void clear(int width, int height) {
			field.clear(width,height);
		}

		void clear(Index_t index) {
			field.clear(index);
		}

		bool move(Index2 ind, MoveDirs dir);
		bool move(int index, MoveDirs dir);
		bool move(int index, MoveDirs dir, int stepLength);

		void flip(int index_1, int index_2) {
			field.flip(index_1, index_2);
		}
		void flip(Index2 ind_1, Index2 ind_2) {
			field.flip(ind_1, ind_2);
		}
		void flip(int index, Index2 motionVector) {
			field.flip(index, motionVector);
		}


		Index_t getProjectionIndex(Index_t index, MoveDirs direction) {
			Index2 motion = LUT_MV.get(direction);
			Index_t targetIndex = getDirIndex(index, motion);
			return targetIndex;
		}

		private:
		Index_t getDirIndex(Index_t index, Index2 motion);

	}; //class Domain



}//namespace simulate