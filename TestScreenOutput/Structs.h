#pragma once
#include <Windows.h>

struct RenderState {
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;
};

struct Index2 {
	int i;
	int j;
	int data[2]{ i,j };
};