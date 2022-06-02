#pragma once
#include "MT_subDomain.h"

namespace multi_t {
	class MT_sd_Controller
	{
	public:
		MT_sd_Controller(int box_size, simulate::Simulator* controller) {
			fController = controller;
			iSize = box_size;
			jSize = box_size;
			divideField();
		};


		void multiThread(int nThreads);

	private:
		simulate::Simulator* fController;
		std::vector<MT_subDomain> domainsList;

		int iSize;
		int jSize;
		int NIsubs;
		int NJsubs;
		int nSubs;

		void divideField(void);

	public:

		inline Index2 getIJsize(void) { Index2 IJsize = { iSize, jSize }; return IJsize; }
		inline int getSubs(void) {	return nSubs;}
		inline Index2 getIJsubs(void) { Index2 IJsubs = { NIsubs, NJsubs }; return IJsubs;}

	};

} //namespace