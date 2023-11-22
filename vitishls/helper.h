#pragma once
#include "definitions.h"

fixed_t reLu (fixed_t x);

fixed_t reLu (fixed_t x){
	if (x > 0){
		return x;
	}
	return 0;
}
