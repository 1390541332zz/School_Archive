## Generated SDC file "fir.sdc"

## Copyright (C) 2017  Intel Corporation. All rights reserved.
## Your use of Intel Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Intel Program License 
## Subscription Agreement, the Intel Quartus Prime License Agreement,
## the Intel MegaCore Function License Agreement, or other 
## applicable license agreement, including, without limitation, 
## that your use is for the sole purpose of programming logic 
## devices manufactured by Intel and sold by Intel or its 
## authorized distributors.  Please refer to the applicable 
## agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus Prime"
## VERSION "Version 17.0.2 Build 602 07/19/2017 SJ Lite Edition"

## DATE    "Tue Apr 02 07:50:37 2019"

##
## DEVICE  "5CSEMA5F31C6"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {CLOCK_50} -period 20.000 -waveform { 0.000 10.000 } [get_ports {CLOCK_50}]


#**************************************************************
# Create Generated Clock
#**************************************************************



#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************

set_clock_uncertainty -rise_from [get_clocks {CLOCK_50}] -rise_to [get_clocks {CLOCK_50}] -setup 0.170  
set_clock_uncertainty -rise_from [get_clocks {CLOCK_50}] -rise_to [get_clocks {CLOCK_50}] -hold 0.060  
set_clock_uncertainty -rise_from [get_clocks {CLOCK_50}] -fall_to [get_clocks {CLOCK_50}] -setup 0.170  
set_clock_uncertainty -rise_from [get_clocks {CLOCK_50}] -fall_to [get_clocks {CLOCK_50}] -hold 0.060  
set_clock_uncertainty -fall_from [get_clocks {CLOCK_50}] -rise_to [get_clocks {CLOCK_50}] -setup 0.170  
set_clock_uncertainty -fall_from [get_clocks {CLOCK_50}] -rise_to [get_clocks {CLOCK_50}] -hold 0.060  
set_clock_uncertainty -fall_from [get_clocks {CLOCK_50}] -fall_to [get_clocks {CLOCK_50}] -setup 0.170  
set_clock_uncertainty -fall_from [get_clocks {CLOCK_50}] -fall_to [get_clocks {CLOCK_50}] -hold 0.060  


#**************************************************************
# Set Input Delay
#**************************************************************

set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {KEY[0]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {KEY[1]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {KEY[2]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {KEY[3]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[0]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[1]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[2]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[3]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[4]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[5]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[6]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[7]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[8]}]
set_input_delay -add_delay  -clock [get_clocks {CLOCK_50}]  0.000 [get_ports {SW[9]}]


#**************************************************************
# Set Output Delay
#**************************************************************

#**************************************************************
# Set Clock Groups
#**************************************************************



#**************************************************************
# Set False Path
#**************************************************************



#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

