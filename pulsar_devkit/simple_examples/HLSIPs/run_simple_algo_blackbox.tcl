# Create a project
open_project -reset proj0

# Program Control Options
# "SCALAR", "STREAM"
set inputStyle "STREAM"

# Add design files
add_files src/simple_algo_blackbox.cpp -cflags "-std=c++14 -D${inputStyle} -DDEBUG=0"
# Add test bench & files
add_files -tb simple_algo_blackbox_test.cpp -cflags "-std=c++14 -D${inputStyle}"
# JSON file and top-level function
if {$inputStyle == "STREAM"} {
	add_files -blackbox src/simple_algo_blackbox_stream.json

	# Set the top-level function
	set_top simple_algo_blackbox_stream
} else {
	add_files -blackbox src/simple_algo_blackbox.json

	# Set the top-level function
	set_top simple_algo_blackbox
}

# ########################################################
# Create a solution
open_solution -reset solution1_rtl_as_blackbox_${inputStyle}
# Define technology and clock rate
set_part  {xcvu9p-flga2104-2l-e}
create_clock -period "320MHz"
config_compile -name_max_length 100

# config_dataflow -default_channel fifo -fifo_depth 20

# Set to 0: to run setup
# Set to 1: to run setup and synthesis
# Set to 2: to run setup, synthesis and RTL simulation
# Set to 3: to run setup, synthesis, RTL simulation and RTL synthesis
# Any other value will run setup only
set hls_exec 2
csim_design

# Set any optimization directives
# End of directives

if {$hls_exec == 1} {
	# Run Synthesis and Exit
	csynth_design
	
} elseif {$hls_exec == 2} {
	# Run Synthesis, RTL Simulation and Exit
	csynth_design	
	cosim_design -trace_level all -rtl verilog -verbose
} elseif {$hls_exec == 3} { 
	# Run Synthesis, RTL Simulation, RTL implementation and Exit
	csynth_design	
	cosim_design -trace_level all -rtl verilog -verbose
	export_design -rtl verilog -flow impl
} elseif {$hls_exec ==4} {
	# Run Synthesis, RTL implementation and Exit
	# Only for expert use or testing purposes
	csynth_design
	export_design -rtl verilog -flow impl
} else {
	# Default is to exit after setup
	csynth_design
}

exit
