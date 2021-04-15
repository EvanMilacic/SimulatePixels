#include <Windows.h>
//#include <iostream>


#include "Structs.h"
#include "utils.cpp"
#include "Globals.h"

#include "ScreenRenderer.h"
#include "Simulator.h"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg,
	_In_ WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	}break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		renderState.width = rect.right - rect.left;
		renderState.height = rect.bottom - rect.top;

		int buffer_size = renderState.width * renderState.height * sizeof(u32);

		if (renderState.memory) VirtualFree(renderState.memory, 0, MEM_RELEASE);
		renderState.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		renderState.bitmap_info.bmiHeader.biSize = sizeof(renderState.bitmap_info.bmiHeader);
		renderState.bitmap_info.bmiHeader.biWidth = renderState.width;
		renderState.bitmap_info.bmiHeader.biHeight = renderState.height;
		renderState.bitmap_info.bmiHeader.biPlanes = 1;
		renderState.bitmap_info.bmiHeader.biBitCount = 32;
		renderState.bitmap_info.bmiHeader.biCompression = BI_RGB;

	}break;
	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	}
	return result;
}
 

int WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,
			int nShowCmd)
{

	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register Class
	RegisterClass(&window_class);

	

	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, "My First Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);


	//Create ScreenRenderer & Simulator
	render::ScreenRenderer renderer;
	simulate::Simulator simulator(renderState);

	while (running) {

		// Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		// Simulate
		//renderer.RenderBackground(renderState);
		renderer.UpdateScreen(renderState);
		simulator.SimulateDomain();

		// Render Game
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
	}
}