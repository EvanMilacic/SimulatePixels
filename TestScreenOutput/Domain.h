#pragma once
#include <vector>


#include "Globals.h"
#include "Defines.h"
#include "Enums.h"
#include "MyMath.h"
#include "Index2.h"
#include "Motion2.h"

namespace simulate {

	class Domain
	{
	private:
		Index_t nWidth;
		Index_t nHeight;
		Index_t nSize;
		std::vector<MatType> field;

		Index_t CalcIndex(Index_t i, Index_t j) {
			return nWidth * j + i;
		};
		
		Index_t CalcIndex(Index2 ind) {
			return CalcIndex(ind.i, ind.j);
		}

		Index2 CalcIndex2(Index_t index) {
			Index2 indices{ (Index_t)(index - floor(index / nWidth) * nWidth), (Index_t)floor(index / nWidth) };
			return indices;
		}

		Index2 CalcIndex2(Index_t index, MoveDirs direction) {
			Index2 ind = CalcIndex2(index);
			Motion2 dir = getMotionVector(direction);
			ind += dir;
			return ind;
		}

		bool isDefault(Index_t index) {
			return (field[index] == MatType::Default);
		}


	public:
		Domain(Index_t width, Index_t height) { setSize(width, height); };
		~Domain() {};


		// Setters
		void setSize(Index_t width, Index_t height) {
			nWidth = width;
			nHeight = height;
			field.resize(nWidth * nHeight);
		}

		void set(Index_t width, Index_t height, MatType type) {
			Index_t index = CalcIndex(width, height);
			field[index] = type;
		}

		void set(Index2 ind, MatType type) {
			set(ind.i, ind.j, type);
		}

		void set(Index_t index, MatType type) {
			field[index] = type;
		}

		void clear(Index_t width, Index_t height) {
			Index_t index = CalcIndex(width, height);
			field[index] = MatType::Default;
		}

		void clear(Index_t index) {
			field[index] = MatType::Default;
		}

		//Getters
		Index_t getSize(void) { return static_cast<Index_t>(field.size()); };
		Index_t getWidth(void) { return nWidth; };
		Index_t getHeight(void) { return nHeight; };

		bool isOnEdge(Index_t index);
		bool isOnEdge(Index2 ind);

		MatType at(Index2 ind) {
			return at(ind.i, ind.j);
		}

		MatType at(Index_t width, Index_t height) {
			Index_t index = CalcIndex(width, height);
			return at(index);
		}

		MatType at(Index_t index) {
				return field[index];
		}

		MatType at(Index2 ind, MoveDirs direction) {
			Index_t index = CalcIndex(ind);
			return at(index, direction);
		}

		MatType at(Index_t index, MoveDirs direction) {
			Index2 ind_dir = CalcIndex2(index,direction);
			return at(ind_dir);
		}

		//move operations
		bool move(Index2 ind, MoveDirs dir);
		bool move(Index_t index, MoveDirs dir);
		bool move(Index_t index, MoveDirs dir, Index_t stepLength);

		void flip(Index_t index_1, Index_t index_2) {
			MatType temp = field[index_1];
			field[index_1] = field[index_2];
			field[index_2] = temp;
		}
		void flip(Index2 ind_1, Index2 ind_2) {
			Index_t index_1 = CalcIndex(ind_1);
			Index_t index_2 = CalcIndex(ind_2);
			flip(index_1, index_2);
		}
		void flip(Index_t index, MoveDirs direction) {
			Index2 ind = CalcIndex2(index);
			Index2 ind_dir = CalcIndex2(index, direction);
			flip(ind, ind_dir);
		}

		Index_t getProjectionIndex(Index_t index, MoveDirs direction) {
			Motion2 motion = getMotionVector(direction);
			Index_t targetIndex = getDirIndex(index, motion);
			return targetIndex;
		}

		private:
		Index_t getDirIndex(Index_t index, Motion2 motion);
		Motion2 getMotionVector(MoveDirs dir);

	}; //class Domain



}//namespace simulate