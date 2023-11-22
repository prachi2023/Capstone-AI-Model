#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "definitions.h"
#include "layers.h"
#include <iostream>
#include <math.h>


void model(hls::stream<ap_axis<32,2,5,6> > &A, // 32 is data width, 2: 2 channels
		hls::stream< ap_axis<32,2,5,6> > &B){

	//Set the variable to stream data using the AXIS protocol
	#pragma HLS INTERFACE axis port = A
	#pragma HLS INTERFACE axis port = B
	#pragma hls interface s_axilite port=return

	fixed_t readings[NUM_READINGS][NUM_SAMPLES];
	fixed_t pool_input[FILTERS][POOL_INPUT_ROWS][POOL_INPUT_COLS];
	fixed_t flat_input[FILTERS][FLAT_INPUT_ROWS][FLAT_INPUT_COLS];
	fixed_t dense_input[DENSE_INPUT_SIZE];
	fixed_t dense2_input[DENSE_SIZE1];
	fixed_t dense3_input[DENSE_SIZE2];
	fixed_t model_output[NUM_CLASSES];

	ap_axis<32,2,5,6> tmp;

	for (int i = 0; i < NUM_READINGS; i ++){
		for (int j = 0; j < NUM_SAMPLES; j++){
			A.read(tmp);
			readings[i][j] = fixed_t(float(tmp.data) / pow(2,20));
		}
	}
	#pragma dataflow
	conv(readings, pool_input);

	//pool
	MaxPool(pool_input, flat_input);

	flatten(flat_input, dense_input);

	dense(dense_input, dense2_input);

	dense2(dense2_input, dense3_input);

	dense3(dense3_input, model_output);

	//get predicted class
	fixed_t max = model_output[0];
	int index = 0;
	ap_axis<32,2,5,6> result;

	result = tmp;

	for (int i = 0; i < NUM_CLASSES; i ++){
		if (model_output[i] > max){
			index = i;
			max = model_output[i];
		}
	}
	result.last = 1;
	result.data = index;
	B.write(result);
}

