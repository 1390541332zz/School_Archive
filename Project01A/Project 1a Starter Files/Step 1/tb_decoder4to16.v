// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 

////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    tb_decoder4to16.v
// Author:      Jason Thweatt
// Date:        02 June 2017
// Version:     1
// Description: This file contains a test bench for the 4-to-16 decoder.
//              We are using it here as an introduction to the ModelSim environment.
//              The testbench is defined behaviorally. It uses a procedure to define the input
//              waveform.

// Testbenches don't have arguments. Instead, the values that we want to modify are regs. ANY VALUE
// THAT IS THE TARGET OF A PROCEDURE MUST BE A REG. The values that we wish to observe are wires.

module tb_decoder4to16();
   reg         enable;
   reg   [3:0] dec_in;
   wire [15:0] dec_out;

   reg   [4:0] count;

// Instantiate the decoder (the identifier is DUT, or Device Under Test)

   decoder4to16 DUT1(enable, dec_in, dec_out);

// Test input waveform - defined as an initial block (procedure)

   initial begin
      dec_in = 4'b0000;		// At time t = 0, dec_in = 0000 and the decoder is DISABLED.
      enable = 1'b1;
      #20;  			// Wait for 20 ns
      enable = 1'b0;		// Enable the decoder.
    	
// We can use a loop to avoid long procedures. There are many other options to write test benches easily!
// With the decoder enabled, the FOR-loop causes dec_in to take in each possible 4-bit value for 20 ns.

      for(count = 0; count < 16; count = count + 1) begin
         dec_in = count[3:0];
         #20;
      end

      dec_in = 4'b0000;		// Set dec_in = 0000.
      #20;			// Wait for 20 ns.
      enable = 1'b1;		// Disable the decoder.
      #20;			// Wait for 20 ns.
   end

endmodule
