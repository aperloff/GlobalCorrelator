#include <cmath>
#include <algorithm>
#include "src/simple_algo_apfixed_logic.h"
#include "ap_int.h"
#include "ap_fixed.h"

void simple_algo_apfixed_logic_ref( ap_uint<12> inA, 
								    ap_fixed<12, 5, AP_RND_CONV, AP_SAT> inB, 
								    ap_uint<1>  &outA , 
								    ap_uint<1>  &outB ) {

	outA = !inA;
	outB = !inB;
}

