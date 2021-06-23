#include "simple_algo_apfixed_logic.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#ifndef __SYNTHESIS__
#include <cstdio>

#endif

void simple_algo_apfixed_logic_hw( int_t inA, fixed_t inB, out_t &outA , out_t &outB ) {
	outA = !inA;
	outA = outA | inA[TOTAL_SIZE-1];
	outB = !inB;
	outB = outB | inB[TOTAL_SIZE-1];
}

void simple_algo_apfixed_logic_hw_loop( int_t inputs[SIZE_D1], count_t &counter_int, count_t &counter_fixed ) {
	for (unsigned int index = 0; index < SIZE_D1; ++index) {
		int_t input = inputs[index];
		int_t inA = input;
		fixed_t inB = 0;
		inB.V = input(11,0);
		out_t outA_int = 0;
		out_t outB_fixed = 0;
		
		simple_algo_apfixed_logic_hw(inA, inB, outA_int, outB_fixed);
		counter_int += outA_int;
		counter_fixed += outB_fixed;
	}
}
