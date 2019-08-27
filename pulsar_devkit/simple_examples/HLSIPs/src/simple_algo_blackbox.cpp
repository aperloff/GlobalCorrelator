#include "simple_algo_blackbox.h"

#ifdef SCALAR

//--------------------------------------------------------
void rtl_simple_algo_blackbox(data_t  a1, data_t  a2, data_t  a3, data_t  a4,
							  data_t  b1, data_t  b2, data_t  b3, data_t  b4,
							  data_t &z1, data_t &z2, data_t &z3, data_t &z4) {
	#pragma HLS inline=off
	z1=a1+b1;
	z2=a2+b2;
	z3=a3+b3;
	z4=a4+b4;
}

//--------------------------------------------------------
void simple_algo_blackbox(data_t  a1, data_t  a2, data_t  a3, data_t  a4,
						  data_t  b1, data_t  b2, data_t  b3, data_t  b4,
						  data_t &sigma) {
	data_t tmp1, tmp2,tmp3, tmp4;
	rtl_simple_algo_blackbox(a1, a2, a3, a4, b1, b2, b3, b4, tmp1, tmp2, tmp3, tmp4);
	sigma = tmp1 + tmp2 + tmp3 + tmp4;
}

#else

//--------------------------------------------------------
void read_write(hls::stream<data_v> & a_read, hls::stream<data_v> & a_write,
				hls::stream<data_v> & b_read, hls::stream<data_v> & b_write) {
	//This pipeline seems to be supurfluous
	//It does set the II=1 in the report, but doesn't change any of the output latency
	//With:    Latency=0 II=1
	//Without: Latency=0 II=0
	#pragma HLS pipeline II=1
	for (unsigned int i=0; i<kDepth; i++) {
		a_write.write(a_read.read());
		b_write.write(b_read.read());
	}
}

//--------------------------------------------------------
void rtl_simple_algo_blackbox_stream(hls::stream<ap_uint<kWidth*kSize> > & artl, hls::stream<ap_uint<kWidth*kSize> > & brtl,
									 hls::stream<ap_uint<kWidth*kSize> > & z) {
	#pragma HLS inline=off
	#pragma HLS pipeline II=1
	ap_uint<kWidth*kSize>  a_tmp=0, b_tmp=0;
	for (unsigned int i=0; i<kDepth; i++) {
		a_tmp = artl.read();
		//printf("a_tmp=%i\n",int(a_tmp));
		b_tmp = brtl.read();
		//printf("b_tmp=%i\n",int(b_tmp));
#ifdef DEEPSTREAM
		z.write(a_tmp+b_tmp);
#else
		z.write((data_v(a_tmp(43,33) + b_tmp(43,33))<<(kSize*3)) +
				(data_v(a_tmp(32,22) + b_tmp(32,22))<<(kSize*2)) +
				(data_v(a_tmp(21,11) + b_tmp(21,11))<<(kSize*1)) +
				(data_v(a_tmp(10,0) + b_tmp(10,0))<<(kSize*0)));
#endif		
	}
}
/*
void rtl_simple_algo_blackbox_stream(ap_uint<kWidth*kSize> artl, ap_uint<kWidth*kSize> brtl,
									 hls::stream<ap_uint<kWidth*kSize> > & z) {
	#pragma HLS inline=off
	#pragma HLS pipeline II=1
	z.write(artl+brtl);
}
*/

//--------------------------------------------------------
void sum(hls::stream<ap_uint<kWidth*kSize> > & z, data_t &sigma) {
	#pragma HLS pipeline II=1
	data_v tmp = 0;
	sigma = 0;
	for (unsigned int i=0; i<kDepth; i++) {
		tmp = z.read();
#ifdef DEEPSTREAM
		sigma += tmp;
#else
	sigma = tmp(10,0) + tmp(21,11) + tmp(32,22) + tmp(43,33);
#endif
	}
}

//--------------------------------------------------------
void simple_algo_blackbox_stream(hls::stream<data_v> & a, hls::stream<data_v> & b, data_t &sigma) {
	#pragma HLS dataflow
	hls::stream<ap_uint<kWidth*kSize> > a_top, b_top, z;
	read_write(a,a_top,b,b_top);
	rtl_simple_algo_blackbox_stream(a_top, b_top, z);    
	sum(z,sigma);
}
/*
void simple_algo_blackbox_stream(hls::stream<data_v> & a, hls::stream<data_v> & b, data_t &sigma) {
	#pragma HLS dataflow
	ap_uint<kWidth*kSize> a_top, b_top;
	hls::stream<ap_uint<kWidth*kSize> > z;
	for (unsigned int i=0; i<kDepth; i++) {
		a_top = a.read();
		b_top = b.read();
		rtl_simple_algo_blackbox_stream(a_top, b_top, z);
	}
	sum(z,sigma);
}
*/
#endif
