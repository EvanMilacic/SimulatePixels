#pragma once

// Platform-agnostic description of the render target: a width*height buffer
// of packed 0xRRGGBB pixels (same layout DrawSimulation() writes), owned and
// allocated by whichever platform backend is in use (Win32/GDI, SDL2, ...).
// BITMAPINFO is a GDI/Win32-only concept, so it is NOT part of this struct;
// win32_platform.cpp keeps its own local BITMAPINFO instead.
struct RenderState {
	int height, width;
	void* memory;
};