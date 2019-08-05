#include "ap_int.h"
#include "hls_stream.h"
#ifndef __SYNTHESIS__
#include <iostream>
#endif

#define kSize 11
typedef ap_uint<kSize> data_t;
//typedef struct { data_t data[4]; } data_v;
//typedef ap_uint<44> data_v;
typedef int64_t data_v;

void rtl_simple_algo_blackbox(data_t  a1, data_t  a2, data_t  a3, data_t  a4,
							  data_t  b1, data_t  b2, data_t  b3, data_t  b4,
							  data_t &z1, data_t &z2, data_t &z3, data_t &z4);
void simple_algo_blackbox(data_t  a1, data_t  a2, data_t  a3, data_t  a4,
						  data_t  b1, data_t  b2, data_t  b3, data_t  b4,
						  data_t &sigma);

data_t getValue(int offset, data_v value);
void rtl_simple_algo_blackbox_stream(hls::stream<data_v> & a, hls::stream<data_v> & b,
									 data_t &z1, data_t &z2, data_t &z3, data_t &z4);
void simple_algo_blackbox_stream(hls::stream<data_v> & a, hls::stream<data_v> & b, data_t &sigma);
