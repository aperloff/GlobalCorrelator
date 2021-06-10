#ifndef SIMPLE_ALGO_APFIXED_LOGIC_H
#define SIMPLE_ALGO_APFIXED_LOGIC_H

#include "ap_int.h"
#include "ap_fixed.h"

void simple_algo_apfixed_logic_ref( ap_uint<12> inA, 
								    ap_fixed<12, 5, AP_RND_CONV, AP_SAT> inB, 
								    ap_uint<1>  &outA , 
								    ap_uint<1>  &outB );
                                    
void simple_algo_apfixed_logic_hw( ap_uint<12> inA, 
								   ap_fixed<12, 5, AP_RND_CONV, AP_SAT> inB, 
								   ap_uint<1>  &outA , 
								   ap_uint<1>  &outB );

#endif
