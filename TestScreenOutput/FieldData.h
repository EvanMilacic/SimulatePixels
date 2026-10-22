#pragma once

#include "Defines.h"

struct FieldData {
	Index_t Nx;
	Index_t Ny;
	Index_t Size;

	void clear(void) {
		Nx = 0;
		Ny = 0;
		Size = 0;
	}
};