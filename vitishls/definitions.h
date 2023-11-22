#pragma once
#include "ap_fixed.h"

typedef ap_fixed<32,9> fixed_t;

#define NUM_CLASSES 10

#define NUM_SAMPLES 30
#define NUM_READINGS 12
#define NUM_CHANNELS 1

#define CONV_KERNEL_ROW 3
#define CONV_KERNEL_COL 3
#define FILTERS 32
#define CONV_STRIDE 1

#define POOL_INPUT_ROWS 10
#define POOL_INPUT_COLS 28

#define POOL_KERNEL_SIZE_ROW 2
#define POOL_KERNEL_SIZE_COL 2

#define POOL_STRIDE_ROW 2
#define POOL_STRIDE_COL 2


#define DENSE_INPUT_SIZE 2240
#define DENSE_SIZE1 64
#define DENSE_SIZE2 32

#define FLAT_INPUT_ROWS 5
#define FLAT_INPUT_COLS 14

