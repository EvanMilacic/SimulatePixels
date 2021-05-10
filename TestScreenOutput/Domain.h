#pragma once
#include <vector>


#include "Globals.h"
#include "Enums.h"
#include "MyMath.h"

namespace simulate {

	class Domain
	{
	private:
		int nWidth;
		int nHeight;
		int nSize;
		std::vector<MatType> field;

		int CalcIndex(int i, int j) {
			return nWidth * j + i;
		};
		
		int CalcIndex(Index2 ind) {
			return CalcIndex(ind.i, ind.j);
		}

		Index2 CalcIndex2(int index) {
			Index2 indices{ (int)(index - floor(index / nWidth) * nWidth), (int)floor(index / nWidth) };
			return indices;
		}

		Index2 CalcIndex2(int index, MoveDirs direction) {
			Index2 ind = CalcIndex2(index);
			Index2 dir = getMotionVector(direction);
			ind += dir;
			return ind;
		}

		bool isDefault(Index_t index) {
			return (field[index] == MatType::Default);
		}


	public:
		Domain(int width, int height) { setSize(width, height); };
		~Domain() {};


		// Setters
		void setSize(int width, int height) {
			nWidth = width;
			nHeight = height;
			field.resize(nWidth * nHeight);
		}

		void set(int width, int height, MatType type) {
			int index = CalcIndex(width, height);
			field[index] = type;
		}

		void set(Index2 ind, MatType type) {
			set(ind.i, ind.j, type);
		}

		void set(int index, MatType type) {
			field[index] = type;
		}

		void clear(int width, int height) {
			int index = CalcIndex(width, height);
			field[index] = MatType::Default;
		}

		void clear(Index_t index) {
			field[index] = MatType::Default;
		}

		//Getters
		int getSize(void) { return field.size(); };
		int getWidth(void) { return nWidth; };
		int getHeight(void) { return nHeight; };

		bool isOnEdge(Index_t index);
		bool isOnEdge(Index2 ind);

		MatType at(Index2 ind) {
			return at(ind.i, ind.j);
		}

		MatType at(int width, int height) {
			int index = CalcIndex(width, height);
			return at(index);
		}

		MatType at(int index) {
				return field[index];
		}

		MatType at(Index2 ind, MoveDirs direction) {
			int index = CalcIndex(ind);
			return at(index, direction);
		}

		MatType at(int index, MoveDirs direction) {
			Index2 ind_dir = CalcIndex2(index,direction);
			return at(ind_dir);
		}

		//move operations
		bool move(Index2 ind, MoveDirs dir);
		bool move(int index, MoveDirs dir);
		bool move(int index, MoveDirs dir, int stepLength);

		void flip(int index_1, int index_2) {
			MatType temp = field[index_1];
			field[index_1] = field[index_2];
			field[index_2] = temp;
		}
		void flip(Index2 ind_1, Index2 ind_2) {
			int index_1 = CalcIndex(ind_1);
			int index_2 = CalcIndex(ind_2);
			flip(index_1, index_2);
		}
		void flip(int index, MoveDirs direction) {
			Index2 ind = CalcIndex2(index);
			Index2 ind_dir = CalcIndex2(index, direction);
			flip(ind, ind_dir);
		}

		Index_t getProjectionIndex(Index_t index, MoveDirs direction) {
			Index2 motion = getMotionVector(direction);
			Index_t targetIndex = getDirIndex(index, motion);
			return targetIndex;
		}

		private:
		Index_t getDirIndex(Index_t index, Index2 motion);
		Index2 getMotionVector(MoveDirs dir);

	}; //class Domain



}//namespace simulate