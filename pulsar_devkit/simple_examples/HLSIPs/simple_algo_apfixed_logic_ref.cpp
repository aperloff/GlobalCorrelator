#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include "src/simple_algo_apfixed_logic.h"
#include "ap_int.h"
#include "ap_fixed.h"

void simple_algo_apfixed_logic_ref( int_t inA, fixed_t inB, out_t &outA, out_t &outB ) {
	outA = !inA;
	outA = outA | inA[TOTAL_SIZE-1];
	outB = !inB;
	outB = outB | inB[TOTAL_SIZE-1];
}

void simple_algo_apfixed_logic_ref_loop( std::vector<int_t> inputs, count_t &counter_int, count_t &counter_fixed ) {
	for (unsigned int index = 0; index < inputs.size(); ++index) {		
		int_t input = inputs.at(index); 
		int_t inA = input;
		fixed_t inB = 0;
		inB.V = input(11,0);
		out_t outA_int = 0;
		out_t outB_fixed = 0;

		simple_algo_apfixed_logic_ref(inA, inB, outA_int, outB_fixed);
		counter_int += outA_int;
		counter_fixed += outB_fixed;
	}
}
