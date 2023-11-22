#pragma once


void conv(fixed_t (*input)[NUM_SAMPLES], fixed_t (*output)[POOL_INPUT_ROWS][POOL_INPUT_COLS]);
void MaxPool(fixed_t (*input)[POOL_INPUT_ROWS][POOL_INPUT_COLS],
		fixed_t  (*output)[FLAT_INPUT_ROWS][FLAT_INPUT_COLS]);
void AvgPool(fixed_t (*input)[POOL_INPUT_ROWS][POOL_INPUT_COLS],
		fixed_t  (*output)[FLAT_INPUT_ROWS][FLAT_INPUT_COLS]);
void flatten(fixed_t  (*input)[FLAT_INPUT_ROWS][FLAT_INPUT_COLS], fixed_t* output);
void dense(fixed_t* input, fixed_t* output);
void dense2(fixed_t* input, fixed_t* output);
void dense3(fixed_t* input, fixed_t* output);
