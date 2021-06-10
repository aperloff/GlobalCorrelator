#include <cstdio>
#include "src/simple_algo_apfixed_logic.h"
#include "ap_int.h"
#include "ap_fixed.h"

#define NTEST 1


int main() {
	
	ap_uint<12> inA;
	ap_fixed<12, 5, AP_RND_CONV, AP_SAT> inB;
	ap_uint<1> outA;
	ap_uint<1> outB;

	for (int test = 1; test <= NTEST; ++test) {

		inA = 1;
		inB = 1;
		outA = 0;
		outB = 0;

		simple_algo_apfixed_logic_ref(inA, inB, outA, outB);
		printf( "ref test: \n\tap_uint in %i -> ap_uint !in %i \n\tap_fixed in %f -> ap_uint !in %i\n", int(inA), int(outA), float(inB), int(outB) );
		
		simple_algo_apfixed_logic_hw(inA, inB, outA, outB);
		printf( "hw test: \n\tap_uint in %i -> ap_uint !in %i \n\tap_fixed in %f -> ap_uint !in %i\n", int(inA), int(outA), float(inB), int(outB) );


	}

	return 0;
}
