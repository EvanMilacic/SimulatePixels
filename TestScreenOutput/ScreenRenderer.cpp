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

	void ScreenRenderer::DrawRectangle(RenderState& renderState) {
		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++) {
			for (int x = 0; x < renderState.width; x++) {
				if (x > 0.25 * renderState.width && x < renderState.width * 0.75 && y > 0.5 * renderState.height && y < renderState.height * 0.75) {
					*pixel++ = x * y;
				}
				else {
					*pixel++ = *pixel;
				}
			}
		}
	}

	void ScreenRenderer::UpdateScreen(RenderState &renderState, simulate::Simulator* simulation) {

		DrawSimulation(renderState,simulation);
	}

	void ScreenRenderer::DrawSimulation(RenderState& renderState,simulate::Simulator* simulation) {
		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (Index_t y = 0; y < renderState.height; y++) {
			for (Index_t x = 0; x < renderState.width; x++) {
				*pixel++ = simulation->getCellColor({ x, y });
			}
		}
	}

} // Namespace render