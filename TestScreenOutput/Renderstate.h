#pragma once
#include <Windows.h>

struct RenderState {
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;
};