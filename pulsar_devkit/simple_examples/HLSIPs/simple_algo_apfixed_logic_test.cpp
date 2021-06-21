#include <cstdio>
#include <iostream>
#include <vector>
#include "src/simple_algo_apfixed_logic.h"
#include "ap_int.h"
#include "ap_fixed.h"

int main() {
	std::vector<std::vector<int_t>> int_inputs = { {0b000000000000, 0b000000000001}, 
												   {0b111111111111, 0b111111111110}, 
												   {0b100000000000, 0b011111111111}, 
												   {0b000010000000, 0b111101111111},
												   {0b000000000000, 0b000000000001, 0b000000000000, 0b000000000000},
												   {0b100000000000, 0b011111111111, 0b011111111111, 0b011111111111},
												   {0b000001000000, 0b000000110001}, 
												   {0b111111111111, 0b111111111110}, 
												   {0b100000010000, 0b011000111111}, 
												   {0b000011010000, 0b111101100111} };
	count_t errors = 0;

    for (unsigned int input = 0; input < int_inputs.size(); ++input) {
		std::cout << "Inputs #" << input+1 << std::endl;

		count_t sel_tracks_counter_int_ref = 0;
		count_t sel_tracks_counter_fixed_ref = 0;
		simple_algo_apfixed_logic_ref_loop( int_inputs[input],
											sel_tracks_counter_int_ref, 
											sel_tracks_counter_fixed_ref);
		std::cout << "ref ap_uint selected tracks: " << sel_tracks_counter_int_ref << std::endl;
		std::cout << "ref ap_fixed selected tracks: " << sel_tracks_counter_fixed_ref << std::endl;
		
		count_t sel_tracks_counter_int_hw = 0;
		count_t sel_tracks_counter_fixed_hw = 0;
		simple_algo_apfixed_logic_hw_loop( int_inputs[input], 
							  			   sel_tracks_counter_int_hw, 
										   sel_tracks_counter_fixed_hw );
		std::cout << "hw ap_uint selected tracks: " << sel_tracks_counter_int_hw << std::endl;
		std::cout << "hw ap_fixed selected tracks: " << sel_tracks_counter_fixed_hw << std::endl;

		out_t agree = sel_tracks_counter_int_hw + sel_tracks_counter_fixed_hw + sel_tracks_counter_int_ref + sel_tracks_counter_fixed_ref;
		if ((agree != 0) & (agree != 4)) {
			std::cout << "\nValue Disagreement!!!\n" << std::endl;
			errors++;
		} 
	}

	if (!errors) {
		std::cout << "\nAll Values Agree\n" << std::endl;
	}

	return errors;
}
