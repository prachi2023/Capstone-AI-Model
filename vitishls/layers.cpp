#include "definitions.h"
#include "helper.h"
#include "conv2d_weights_15nov_3.h"
#include "dense_weights_15nov_3.h"
#include <iostream>

void conv(fixed_t (*input)[NUM_SAMPLES], fixed_t (*output)[POOL_INPUT_ROWS][POOL_INPUT_COLS]){

	// for each filter
	for (int filter = 0; filter < FILTERS; filter ++){
	#pragma HLS unroll

		//for each POOL_INPUT_ROWS = 14 - 3 + 1
		for (int i = 0; i < POOL_INPUT_ROWS; i++){
			for (int j = 0; j < POOL_INPUT_COLS; j++){
				fixed_t sum = 0;

				//Calculate Filter Value
	            for (int m = 0; m < CONV_KERNEL_ROW; m++) {
	                for (int n = 0; n < CONV_KERNEL_COL; n++) {
	                    sum += input[(i + m)][(j + n)] * conv_weights[filter][m][n];
	                }
	            }
	            output[filter][i][j] = reLu(sum + conv_biases[filter]);
			}
		}
	}
}

void MaxPool(fixed_t (*input)[POOL_INPUT_ROWS][POOL_INPUT_COLS],
		fixed_t (*output)[FLAT_INPUT_ROWS][FLAT_INPUT_COLS]){
	// for each filter
	int count = 0;
	for (int filter = 0; filter < FILTERS; filter ++){
	#pragma HLS unroll

		//for each FLAT_INPUT_ROWS = 12/2
		for (int i = 0; i < FLAT_INPUT_ROWS; i++){
			for (int j = 0; j < FLAT_INPUT_COLS; j++){
				fixed_t max = input[filter][i*POOL_STRIDE_ROW][j*POOL_STRIDE_COL];

				//determine max value
	            for (int m = 0; m < POOL_KERNEL_SIZE_ROW ; m++) {
	                for (int n = 0; n < POOL_KERNEL_SIZE_COL; n++) {
	                	if (input[filter][i*POOL_STRIDE_ROW+m][j*POOL_STRIDE_COL+n] > max){
	                		max = input[filter][i*POOL_STRIDE_ROW+m][j*POOL_STRIDE_COL+n];
	                	}
	                }
	            }
	            output[filter][i][j] = max;
			}
		}
	}
}

void AvgPool(fixed_t (*input)[POOL_INPUT_ROWS][POOL_INPUT_COLS],
		fixed_t (*output)[FLAT_INPUT_ROWS][FLAT_INPUT_COLS]){
	// for each filter
	int count = 0;
	for (int filter = 0; filter < FILTERS; filter ++){
	#pragma HLS unroll

		//for each FLAT_INPUT_ROWS = 12/2
		for (int i = 0; i < FLAT_INPUT_ROWS; i++){
			for (int j = 0; j < FLAT_INPUT_COLS; j++){
				//fixed_t max = input[filter][i*POOL_STRIDE_ROW][j*POOL_STRIDE_COL];

				//Calculate Avg value
				fixed_t avg = 0;
				int divisor = (POOL_KERNEL_SIZE_ROW * POOL_KERNEL_SIZE_COL);
	            for (int m = 0; m < POOL_KERNEL_SIZE_ROW ; m++) {
	                for (int n = 0; n < POOL_KERNEL_SIZE_COL; n++) {
	                	//if (input[filter][i*POOL_STRIDE_ROW+m][j*POOL_STRIDE_COL+n] > max){
	                	avg += input[filter][i*POOL_STRIDE_ROW+m][j*POOL_STRIDE_COL+n] / divisor;
	                	//}
	                }
	            }

	            output[filter][i][j] = avg;
			}
		}
	}
}


void flatten(fixed_t (*input)[FLAT_INPUT_ROWS][FLAT_INPUT_COLS], fixed_t* output){
	// for each filter
	int index = 0;
		//for each FLAT_INPUT_ROWS = 12/2
		for (int i = 0; i < FLAT_INPUT_ROWS; i++){
		#pragma HLS unroll

			for (int j = 0; j < FLAT_INPUT_COLS; j++){
				for (int filter = 0; filter < FILTERS; filter ++){
	            output[index] = input[filter][i][j];
	            index ++;
	        }
		}
	}
}


void dense(fixed_t* input, fixed_t* output){
	// for each neuron
	for (int n = 0; n < DENSE_SIZE1; n++){
	#pragma HLS unroll

		fixed_t sum = 0;
		for (int i = 0; i < DENSE_INPUT_SIZE; i++){
			float in = float(input[i]);
			float weight = float(dense1_weights[n][i]);
			sum += input[i]*dense1_weights[n][i];
			float temp = float(sum);
		}
		// add biass
		sum += dense1_biases[n];
		sum = reLu(sum);


		output[n] = sum;
	}
}

void dense2(fixed_t* input, fixed_t* output){
	// for each neuron
	for (int n = 0; n < DENSE_SIZE2; n++){
	#pragma HLS unroll

		fixed_t sum = 0;
		for (int i = 0; i < DENSE_SIZE1; i++){
			sum += input[i]*dense2_weights[n][i];
		}
		// add bias
		sum += dense2_biases[n];
		sum = reLu(sum);
		output[n] = sum;
	}
}


void dense3(fixed_t* input, fixed_t* output){
	// for each neuron
	for (int n = 0; n < NUM_CLASSES; n++){

		fixed_t sum = 0;
		for (int i = 0; i < DENSE_SIZE2; i++){
			sum += input[i]*dense3_weights[n][i];
		}
		// add bias
		sum += dense3_biases[n];
		output[n] = sum;
	}
}
