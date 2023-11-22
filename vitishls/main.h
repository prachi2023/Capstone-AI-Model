#pragma once
#include "ap_axi_sdata.h"
#include "hls_stream.h"


void model(hls::stream<ap_axis<32,2,5,6> > &A, // 32 is data width, 2: 2 channels
		hls::stream< ap_axis<32,2,5,6> > &B);
