#pragma once
#include "Simulator.h"

namespace multi_t {

	class MT_subDomain
	{
	public:

		MT_subDomain() {
		};

		MT_subDomain(simulate::Simulator* _simulator, int tag, int nWidth, int nHeight, int StartI, int StartJ) {
			simulator = _simulator;
			this->tag = tag;
			width = nWidth;
			height = nHeight;
			iStart = StartI;
			jStart = StartJ;
			nSize = width * height;
		}

		~MT_subDomain() {
		};

		int tag = 0;
		int width = 0;
		int height = 0;

		int iStart = 0;
		int jStart = 0;

		int nSize = 0;

		simulate::Simulator* simulator = nullptr;


	};

}//namespace

