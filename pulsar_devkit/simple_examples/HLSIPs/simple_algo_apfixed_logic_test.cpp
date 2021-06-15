#include <cstdio>
#include <iostream>
#include <vector>
#include "src/simple_algo_apfixed_logic.h"
#include "ap_int.h"
#include "ap_fixed.h"

int main() {
	
   std::vector<ap_uint<12>> int_inputs = {0b000000000000, 0b000000000001, 0b111111111111, 0b111111111110, 0b100000000000, 0b011111111111, 0b000010000000, 0b111101111111};
	
    for (unsigned int input = 0; input < int_inputs.size(); ++input) {
		std::cout << "\nRaw Input (ap_uint Format)= " << int_inputs[input].to_string().c_str() << std::endl;
		ap_uint<12> inA = int_inputs[input];
		ap_fixed<12, 5, AP_RND_CONV, AP_SAT> inB = 0;
        inB.V = int_inputs[input](11,0);
		ap_uint<1> outA_ref = 0;
		ap_uint<1> outB_ref = 0;
		ap_uint<1> outA_hw = 0;
		ap_uint<1> outB_hw = 0;

		simple_algo_apfixed_logic_ref(inA, inB, outA_ref, outB_ref);
		simple_algo_apfixed_logic_hw(inA, inB, outA_hw, outB_hw);

		std::cout << "\tC Code Ref: \n\t\tap_uint input " << inA << " -> ap_uint output (!input) " << outA_ref << " \n\t\tap_fixed input " << inB << " -> ap_uint output (!input) " << outB_ref << std::endl;
		if (outA_ref != outB_ref) {
			printf( "C Code Reference Data Type Discrepency!" );
		}
		std::cout << "\tHW: \n\t\tap_uint input " << inA << " -> ap_uint output (!input) " << outA_hw << " \n\t\tap_fixed input " << inB << " -> ap_uint output (!input) " << outB_hw << std::endl;
		if (outA_hw != outB_hw) {
			printf( "HW Data Type Discrepency!" );
		}

		if (outA_ref != outA_hw) {
			printf( "ap_uint Ref-HW Discrepency!!!" );
		}

		if (outB_ref != outB_hw) {
			printf( "ap_fixed Ref-HW Discrepency!!!" );
		}
	}

	return 0;
}
