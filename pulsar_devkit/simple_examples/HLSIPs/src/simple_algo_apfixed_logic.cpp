#include "simple_algo_apfixed_logic.h"
#include <cmath>
#include <cassert>
#ifndef __SYNTHESIS__
#include <cstdio>
#endif

void simple_algo_apfixed_logic_hw( ap_uint<12> inA, 
								   ap_fixed<12, 5, AP_RND_CONV, AP_SAT> inB, 
								   ap_uint<1>  &outA , 
								   ap_uint<1>  &outB ) {

		outA = !inA;
		outB = !inB;

}
