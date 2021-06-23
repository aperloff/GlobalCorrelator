#ifndef SIMPLE_ALGO_APFIXED_LOGIC_H
#define SIMPLE_ALGO_APFIXED_LOGIC_H

#include <vector>
#include "ap_int.h"
#include "ap_fixed.h"
#include <iostream>

// Types
#define SIZE_D1 2
#define TOTAL_SIZE 12
#define INT_SIZE 5
typedef ap_uint<TOTAL_SIZE> int_t;
typedef ap_fixed<TOTAL_SIZE, INT_SIZE, AP_RND_CONV, AP_SAT> fixed_t;
typedef ap_uint<1> out_t;
typedef ap_uint<10> count_t;

void simple_algo_apfixed_logic_ref( int_t inA, 
								    fixed_t inB, 
								    out_t  &outA , 
								    out_t  &outB );

void simple_algo_apfixed_logic_ref_loop( std::vector<int_t> inputs, 
										 count_t &counter_int, 
										 count_t &counter_fixed );

void simple_algo_apfixed_logic_hw( int_t inA, 
								   fixed_t inB, 
								   out_t  &outA, 
								   out_t  &outB );

void simple_algo_apfixed_logic_hw_loop( int_t inputs[SIZE_D1], 
										count_t &counter_int, 
										count_t &counter_fixed );

#endif
