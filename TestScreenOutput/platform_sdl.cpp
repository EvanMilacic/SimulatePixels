// Cross-platform entry point built on SDL2, replacing the Win32/GDI-only
// win32_platform.cpp. Runs natively on Windows, Linux and macOS, and - when
// compiled with Emscripten against SDL2's web port - in the browser as well.
// The simulation core (Field/Domain/Simulator/materials) is untouched; this
// file only owns the window, the pixel buffer and the main loop.

#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cstdlib>

#include "Renderstate.h"
#include "Globals.h"
#include "ScreenRenderer.h"
#include "Simulator.h"

namespace {

	SDL_Window* window = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Texture* texture = nullptr;

	render::ScreenRenderer screenRenderer;
	simulate::Simulator* simulator = nullptr;

	// (Re)allocates the raw pixel buffer behind RenderState and the SDL
	// texture it gets uploaded to whenever the window size changes.
	void allocateBuffer(int width, int height) {
		if (renderState.memory) {
			free(renderState.memory);
			renderState.memory = nullptr;
		}

		renderState.width = width;
		renderState.height = height;
		renderState.memory = malloc((size_t)width * height * sizeof(unsigned int));

		if (texture) {
			SDL_DestroyTexture(texture);
		}
		// RGB888/XRGB8888 matches the 0x00RRGGBB layout Material::getColor()
		// already produces (the same layout the old 32bpp BI_RGB DIB used).
		texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGB888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	}

	void handleResize(int width, int height) {
		if (width <= 0 || height <= 0) {
			return;
		}
		allocateBuffer(width, height);
		if (simulator) {
			FieldData fData = {
				static_cast<Index_t>(width),
				static_cast<Index_t>(height),
				static_cast<Index_t>(width) * static_cast<Index_t>(height) };
			simulator->setSize(fData);
		}
	}

	// One frame: input, simulate, draw. Called directly in a loop natively,
	// or by the browser's requestAnimationFrame via emscripten_set_main_loop.
	void mainLoopStep() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
					event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					handleResize(event.window.data1, event.window.data2);
				}
				break;
			default:
				break;
			}
		}

		simulator->setCenterSand();

		screenRenderer.UpdateScreen(renderState, simulator);

		simulator->SimulateDomain();

		SDL_UpdateTexture(texture, nullptr, renderState.memory,
			renderState.width * (int)sizeof(unsigned int));
		SDL_RenderClear(sdlRenderer);
		// DrawSimulation() writes row 0 = j=0, which is "down" in material
		// space (where falling materials settle). The old Win32 backend's
		// positive BITMAPINFO.biHeight made GDI treat that as a bottom-up
		// DIB, implicitly flipping it right-side up; SDL textures are always
		// top-down, so flip vertically here to match the original look.
		SDL_RenderCopyEx(sdlRenderer, texture, nullptr, nullptr,
			0.0, nullptr, SDL_FLIP_VERTICAL);
		SDL_RenderPresent(sdlRenderer);
	}

} // namespace

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return 1;
	}

	const int initialWidth = 500;
	const int initialHeight = 250;

	window = SDL_CreateWindow("SimulatePixels",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		initialWidth, initialHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window) {
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		return 1;
	}

	sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!sdlRenderer) {
		sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	}

	allocateBuffer(initialWidth, initialHeight);

	simulate::Simulator sim(renderState);
	simulator = &sim;

#ifdef __EMSCRIPTEN__
	// 0 fps = sync to requestAnimationFrame, 1 = simulate infinite loop.
	emscripten_set_main_loop(mainLoopStep, 0, 1);
#else
	while (running) {
		mainLoopStep();
	}
#endif

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	free(renderState.memory);

	return 0;
}
