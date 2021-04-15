#pragma once
#include <vector>

#include "Material.h"

namespace simulate {
	class Domain
	{
	private:
		int nWidth;
		int nHeight;
		int nSize;
		std::vector<materie::MatType> field;

		int CalcIndex(int i, int j) {
			return nWidth * i + j;
		};


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

		void set(int width, int height, materie::MatType type) {
			int index = CalcIndex(width, height);
			field[index] = type;
		}

		void set(int index, materie::MatType type) {
			field[index] = type;
		}

		void clear(int width, int height) {
			int index = CalcIndex(width, height);
			field[index] = materie::MatType::Default;
		}

		//Getters
		int getSize(void) {
			return nSize;
		}

		materie::MatType at(int width, int height) {
			int index = CalcIndex(width, height);
			return field[index];
		}

		materie::MatType at(int index) {
			return field[index];
		}

	}; //class Domain

}//namespace simulate