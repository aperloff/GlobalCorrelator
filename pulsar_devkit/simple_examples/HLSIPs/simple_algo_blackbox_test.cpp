#include <iostream>
#include "src/simple_algo_blackbox.h"

int main() {

	// Set the test data ------------------------------------
	data_t t_a1[NTEST] = {3,1,2,3};
	data_t t_a2[NTEST] = {4,0,0,0};
	data_t t_a3[NTEST] = {1,0,0,0};
	data_t t_a4[NTEST] = {20,0,0,0};
	data_t t_b1[NTEST] = {7,0,0,0};
	data_t t_b2[NTEST] = {9,0,0,0};
	data_t t_b3[NTEST] = {0,0,0,0};
	data_t t_b4[NTEST] = {1023,0,0,0};

	// Initialize other variables ---------------------------
	data_t t_sigma, t_ref;

	// Perform the tests ------------------------------------
	for (unsigned int test=0; test<NTEST; test++) {
		t_ref = t_a1[test]+t_a2[test]+t_a3[test]+t_a4[test]+t_b1[test]+t_b2[test]+t_b3[test]+t_b4[test];
#ifdef SCALAR
		simple_algo_blackbox(t_a1[test], t_a2[test], t_a3[test], t_a4[test], t_b1[test], t_b2[test], t_b3[test], t_b4[test], t_sigma);
#else
		data_v t_a, t_b;
		hls::stream<data_v> t_a_s, t_b_s;
#ifdef DEEPSTREAM
		for (unsigned int i=0; i<kDepth; i++) {
			t_a_s.write(t_a1[test]); t_a_s.write(t_a2[test]); t_a_s.write(t_a3[test]); t_a_s.write(t_a4[test]);
			t_b_s.write(t_b1[test]); t_b_s.write(t_b2[test]); t_b_s.write(t_b3[test]); t_b_s.write(t_b4[test]);
		}
#else
		t_a = (data_v(t_a4[test])<<(kSize*3)) + (data_v(t_a3[test])<<(kSize*2)) + (data_v(t_a2[test])<<(kSize*1)) + (data_v(t_a1[test])<<(kSize*0));
		t_b = (data_v(t_b4[test])<<(kSize*3)) + (data_v(t_b3[test])<<(kSize*2)) + (data_v(t_b2[test])<<(kSize*1)) + (data_v(t_b1[test])<<(kSize*0));
		t_a_s.write(t_a); t_b_s.write(t_b);
#endif
		simple_algo_blackbox_stream(t_a_s, t_b_s, t_sigma);
#endif
		std::cout << " t_sigma " << (int)t_sigma << " t_ref " << (int)t_ref <<  std::endl;
		if (t_sigma != t_ref) return -1*(test+1);

		/*
		int t_a_s_data_remaining = 0;
		int t_b_s_data_remaining = 0;
		while (!t_a_s.empty()) t_a_s_data_remaining++;
		while (!t_b_s.empty()) t_b_s_data_remaining++;
		if (t_a_s_data_remaining!=0 || t_b_s_data_remaining!=0) {
			if (t_a_s_data_remaining!=0) std::cout << " ERROR::There are " << t_a_s_data_remaining << " units of data remaining in t_a_s!" << std::endl;
			if (t_b_s_data_remaining!=0) std::cout << " ERROR::There are " << t_b_s_data_remaining << " units of data remaining in t_b_s!" << std::endl;
			return -9999;
		}
		*/
	}
	return 0;
}