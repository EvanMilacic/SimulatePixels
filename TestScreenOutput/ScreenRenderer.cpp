#include "ScreenRenderer.h"

namespace render {

	void ScreenRenderer::RenderBackground(RenderState &renderState) {

		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = x * y;
			}
		}
	}

	void ScreenRenderer::ClearScreen(RenderState &renderState) {
		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = 0x000000;
			}
		}
	}


	void ScreenRenderer::UpdateScreen(RenderState &renderState, simulate::Simulator* simulation) {

		DrawSimulation(renderState,simulation);
	}

	void ScreenRenderer::DrawSimulation(RenderState& renderState,simulate::Simulator* simulation) {
		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++) {
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = simulation->getCellColor(y, x);
			}
		}
	}

} // Namespace render