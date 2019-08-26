#include "ap_int.h"
#include "hls_stream.h"

//#include <stdint.h>
//#ifndef __SYNTHESIS__
//#include <iostream>
//#endif

#define kSize 11
typedef ap_uint<kSize> data_t;
typedef ap_uint<44> data_v;

void rtl_simple_algo_blackbox(data_t  a1, data_t  a2, data_t  a3, data_t  a4,
							  data_t  b1, data_t  b2, data_t  b3, data_t  b4,
							  data_t &z1, data_t &z2, data_t &z3, data_t &z4);
void simple_algo_blackbox(data_t  a1, data_t  a2, data_t  a3, data_t  a4,
						  data_t  b1, data_t  b2, data_t  b3, data_t  b4,
						  data_t &sigma);

void sum(hls::stream<data_v> & z, data_t &sigma);
void read_write(hls::stream<data_v> & a_read, hls::stream<data_v> & a_write,
                hls::stream<data_v> & b_read, hls::stream<data_v> & b_write);
void rtl_simple_algo_blackbox_stream(hls::stream<ap_uint<44> > & a, hls::stream<ap_uint<44> > & b, hls::stream<ap_uint<44> > & z);
void simple_algo_blackbox_stream(hls::stream<data_v> & a, hls::stream<data_v> & b, data_t &sigma);
