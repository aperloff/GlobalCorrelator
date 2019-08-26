#include "simple_algo_blackbox.h"

#ifndef STREAM

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
/*
data_t getValue(int offset, data_v value) {
    #pragma HLS pipeline II=1
	data_t ret;
	for (unsigned int i=0; i<kSize; i++) {
		ret[i] = (value>>((offset*kSize)+i)) & 1;
	}
	return ret;
}
*/

//--------------------------------------------------------
void rtl_simple_algo_blackbox_stream(hls::stream<ap_uint<44> > & artl, hls::stream<ap_uint<44> > & brtl,
									 hls::stream<ap_uint<44> > & z) {
	#pragma HLS inline=off
	#pragma HLS pipeline II=1
	ap_uint<44>  a_tmp, b_tmp;
	a_tmp = artl.read();
	b_tmp = brtl.read();
	//z1 = a_tmp.data[0] + b_tmp.data[0];
	//z2 = a_tmp.data[1] + b_tmp.data[1];
	//z3 = a_tmp.data[2] + b_tmp.data[2];
	//z4 = a_tmp.data[3] + b_tmp.data[3];
	
	//z1 = a_tmp(10,0) + b_tmp(10,0);
	//z2 = a_tmp(21,11) + b_tmp(21,11);
	//z3 = a_tmp(32,22) + b_tmp(32,22);
	//z4 = a_tmp(43,33) + b_tmp(43,33);

    //z.write(a_tmp(10,0) + b_tmp(10,0));
    //z.write(a_tmp(21,11) + b_tmp(21,11));
    //z.write(a_tmp(32,22) + b_tmp(32,22));
    //z.write(a_tmp(43,33) + b_tmp(43,33));

	z.write((data_v(a_tmp(43,33) + b_tmp(43,33))<<(kSize*3)) +
	        (data_v(a_tmp(32,22) + b_tmp(32,22))<<(kSize*2)) +
	        (data_v(a_tmp(21,11) + b_tmp(21,11))<<(kSize*1)) +
	        (data_v(a_tmp(10,0) + b_tmp(10,0))<<(kSize*0)));

	//z1 = getValue(0,a_tmp) + getValue(0,b_tmp);
	//z2 = getValue(1,a_tmp) + getValue(1,b_tmp);
	//z3 = getValue(2,a_tmp) + getValue(2,b_tmp);
	//z4 = getValue(3,a_tmp) + getValue(3,b_tmp);
	//#ifndef __SYNTHESIS__
	//std::cout << "a_tmp = " << a_tmp << std::endl;
	//std::cout << "b_tmp = " << b_tmp << std::endl;
	//printf("z1 = a1 + b1 ==> %i = %i + %i\n",int(z1), int(getValue(0,a_tmp)), int(getValue(0,b_tmp)));
	//printf("z2 = a2 + b2 ==> %i = %i + %i\n",int(z2), int(getValue(1,a_tmp)), int(getValue(1,b_tmp)));
	//printf("z3 = a3 + b3 ==> %i = %i + %i\n",int(z3), int(getValue(2,a_tmp)), int(getValue(2,b_tmp)));
	//printf("z4 = a4 + b4 ==> %i = %i + %i\n",int(z4), int(getValue(3,a_tmp)), int(getValue(3,b_tmp)));
	//#endif

	//z.write(getValue(0,a_tmp) + getValue(0,b_tmp));
	//z.write(getValue(1,a_tmp) + getValue(1,b_tmp));
    //z.write(getValue(2,a_tmp) + getValue(2,b_tmp));
    //z.write(getValue(3,a_tmp) + getValue(3,b_tmp));
}

//--------------------------------------------------------
void sum(hls::stream<ap_uint<44> > & z, data_t &sigma) {
	data_v tmp;
	tmp = z.read();
	//printf("tmp(binary) = %s\n",tmp.to_string().c_str());
	sigma = tmp(10,0) + tmp(21,11) + tmp(32,22) + tmp(43,33);
	//printf("sigma(binary) = %s\n",sigma.to_string().c_str());
	//printf("sigma(decimal) = %s\n",sigma.to_string(10).c_str());
}

void read_write(hls::stream<data_v> & a_read, hls::stream<data_v> & a_write,
                hls::stream<data_v> & b_read, hls::stream<data_v> & b_write) {
	//This pipeline seems to be supurfluous
	//It does set the II=1 in the report, but doesn't change any of the output latency
	//With:    Latency=0 II=1
	//Without: Latency=0 II=0
	#pragma HLS pipeline II=1
    a_write.write(a_read.read());
    b_write.write(b_read.read());
}

//--------------------------------------------------------
void simple_algo_blackbox_stream(hls::stream<data_v> & a, hls::stream<data_v> & b, data_t &sigma) {
    #pragma HLS dataflow
    hls::stream<ap_uint<44> > a_top, b_top, z;
    read_write(a,a_top,b,b_top);
    rtl_simple_algo_blackbox_stream(a_top, b_top, z);    
    sum(z,sigma);
}

#endif
