#pragma once
#include "Structs.h"
#include "Simulator.h"

namespace render {
	class ScreenRenderer{

	public:
		ScreenRenderer() {};
		~ScreenRenderer() {};

		static void RenderBackground(RenderState &renderState);
		static void ClearScreen(RenderState &renderState);
		static void DrawRectangle(RenderState& renderState);
		void UpdateScreen(RenderState &renderState, simulate::Simulator* simulation);
		void DrawSimulation(RenderState& renderState, simulate::Simulator* simulation);
		
	private:


	}; //Class ScreenRenderer
} // Namespace render;