#pragma once
#include <vector>

#include "Globals.h"
#include "Structs.h"
#include "Enums.h"
#include "MyMath.h"
#include "Material.h"

namespace simulate {

	class Domain
	{
	private:
		int nWidth;
		int nHeight;
		int nSize;
		std::vector<MatType> field;

		int CalcIndex(int i, int j) {
			return nWidth * i + j;
		};
		
		int CalcIndex(Index2 ind) {
			return CalcIndex(ind.i, ind.j);
		}

		Index2 CalcIndex2(int index) {
			Index2 indices{ index - floor(index / nWidth) * nWidth, floor(index / nWidth) };
			return indices;
		}

		bool isDefault(Index_t index) {
			return (field[index] == MatType::Default);
		}


	public:
		Domain() {};
		Domain(int width, int height) { setSize(width, height); };

		~Domain() {};


		// Setters
		void setSize(int width, int height) {
			nWidth = width;
			nHeight = height;
			nSize = nWidth * nHeight;
			field.resize(nSize);
		}

		void set(int width, int height, MatType type) {
			int index = CalcIndex(width, height);
			field[index] = type;
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
		int getSize(void) { return nSize; };
		int getWidth(void) { return nWidth; };

		MatType at(int width, int height) {
			int index = CalcIndex(width, height);
			return field[index];
		}

		MatType at(int index) {
			return field[index];
		}


		//move operations
		bool move(int index, MoveDirs dir);
		bool move(int index, MoveDirs dir, int stepLength);

	private:
		Index_t getDirIndex(Index_t index, int* motion);
		int* getMotionVector(MoveDirs dir);

	}; //class Domain



}//namespace simulate