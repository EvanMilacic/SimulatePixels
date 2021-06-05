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


		void multiThreadTesting(int nThreads);

	private:
		simulate::Simulator* fController;
		std::vector<MT_subDomain> domainsList;

		int iSize;
		int jSize;
		int NIsubs;
		int NJsubs;
		int nSubs;


		void divideField(void);

	};

} //namespace