#include <iostream>
#include "src/simple_algo_blackbox.h"

int main() {

	data_t t_a1, t_a2, t_a3, t_a4;
	data_t t_b1, t_b2, t_b3, t_b4;
	data_t t_sigma, t_ref;
	#ifdef STREAM
		data_v t_a, t_b;
		hls::stream<data_v> t_a_s, t_b_s;
	#endif

	// Test #1 ----------------------------------------------
	t_a1=3; t_a2=4; t_a3=1; t_a4=20;
	t_b1=7; t_b2=9; t_b3=0; t_b4=1023;
	t_ref = t_a1+t_a2+t_a3+t_a4+t_b1+t_b2+t_b3+t_b4;
	#ifndef STREAM
		simple_algo_blackbox(t_a1, t_a2, t_a3, t_a4, t_b1, t_b2, t_b3, t_b4, t_sigma);
	#else
		t_a = (data_v(t_a4)<<(kSize*3)) + (data_v(t_a3)<<(kSize*2)) + (data_v(t_a2)<<(kSize*1)) + (data_v(t_a1)<<(kSize*0));
		t_b = (data_v(t_b4)<<(kSize*3)) + (data_v(t_b3)<<(kSize*2)) + (data_v(t_b2)<<(kSize*1)) + (data_v(t_b1)<<(kSize*0));
		t_a_s.write(t_a); t_b_s.write(t_b);
		simple_algo_blackbox_stream(t_a_s, t_b_s, t_sigma);
	#endif
	
	std::cout << " t_sigma " << (int)t_sigma << " t_ref " << (int)t_ref <<  std::endl;
	if (t_sigma != t_ref) return -1;

	// Test #2 -----------------------------------------------
	t_a1=1; t_a2=0; t_a3=0; t_a4=0;
	t_b1=0; t_b2=0; t_b3=0; t_b4=0;
	t_ref = t_a1+t_a2+t_a3+t_a4+t_b1+t_b2+t_b3+t_b4;
	#ifndef STREAM
		simple_algo_blackbox(t_a1, t_a2, t_a3, t_a4, t_b1, t_b2, t_b3, t_b4, t_sigma);
	#else
		t_a = (data_v(t_a4)<<(kSize*3)) + (data_v(t_a3)<<(kSize*2)) + (data_v(t_a2)<<(kSize*1)) + (data_v(t_a1)<<(kSize*0));
		t_b = (data_v(t_b4)<<(kSize*3)) + (data_v(t_b3)<<(kSize*2)) + (data_v(t_b2)<<(kSize*1)) + (data_v(t_b1)<<(kSize*0));
		t_a_s.write(t_a); t_b_s.write(t_b);
		simple_algo_blackbox_stream(t_a_s, t_b_s, t_sigma);
	#endif
	
	std::cout << " t_sigma " << (int)t_sigma << " t_ref " << (int)t_ref <<  std::endl;
	if (t_sigma != t_ref) return -2;


	// Test #3 -----------------------------------------------
	t_a1=2; t_a2=0; t_a3=0; t_a4=0;
	t_b1=0; t_b2=0; t_b3=0; t_b4=0;
	t_ref = t_a1+t_a2+t_a3+t_a4+t_b1+t_b2+t_b3+t_b4;
	#ifndef STREAM
		simple_algo_blackbox(t_a1, t_a2, t_a3, t_a4, t_b1, t_b2, t_b3, t_b4, t_sigma);
	#else		
		t_a = (data_v(t_a4)<<(kSize*3)) + (data_v(t_a3)<<(kSize*2)) + (data_v(t_a2)<<(kSize*1)) + (data_v(t_a1)<<(kSize*0));
		t_b = (data_v(t_b4)<<(kSize*3)) + (data_v(t_b3)<<(kSize*2)) + (data_v(t_b2)<<(kSize*1)) + (data_v(t_b1)<<(kSize*0));
		t_a_s.write(t_a); t_b_s.write(t_b);
		simple_algo_blackbox_stream(t_a_s, t_b_s, t_sigma);
	#endif
	
	std::cout << " t_sigma " << (int)t_sigma << " t_ref " << (int)t_ref <<  std::endl;
	if (t_sigma != t_ref) return -3;

	// Test #4 -----------------------------------------------
	t_a1=3; t_a2=0; t_a3=0; t_a4=0;
	t_b1=0; t_b2=0; t_b3=0; t_b4=0;
	t_ref = t_a1+t_a2+t_a3+t_a4+t_b1+t_b2+t_b3+t_b4;
	#ifndef STREAM
		simple_algo_blackbox(t_a1, t_a2, t_a3, t_a4, t_b1, t_b2, t_b3, t_b4, t_sigma);
	#else
		t_a = (data_v(t_a4)<<(kSize*3)) + (data_v(t_a3)<<(kSize*2)) + (data_v(t_a2)<<(kSize*1)) + (data_v(t_a1)<<(kSize*0));
		t_b = (data_v(t_b4)<<(kSize*3)) + (data_v(t_b3)<<(kSize*2)) + (data_v(t_b2)<<(kSize*1)) + (data_v(t_b1)<<(kSize*0));
		t_a_s.write(t_a); t_b_s.write(t_b);
		simple_algo_blackbox_stream(t_a_s, t_b_s, t_sigma);
	#endif
	
	std::cout << " t_sigma " << (int)t_sigma << " t_ref " << (int)t_ref <<  std::endl;
	if (t_sigma != t_ref) return -4;

	return 0;
}
