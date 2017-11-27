////////////////////////////////////////////////////////////////////////////////////////////////////
// File: single_port_ram.v
//
// ******************************************
// YOU ARE NOT PERMITTED TO MODIFY THIS FILE.
// ******************************************
//
// Description: This is a model of a single-port random access memory with a single-cycle
//              read/write address. It serves as the Simple Computer's data memory.
//
// Created: 06/2012, Xin Xin, Virginia Tech
// Modified by P. Athanas, 3/2013 
////////////////////////////////////////////////////////////////////////////////////////////////////

module single_port_ram #(parameter DATA_WIDTH = 8, parameter ADDR_WIDTH = 6)
(
   input  [(DATA_WIDTH - 1):0] data,
   input  [(ADDR_WIDTH - 1):0] addr,
   input  we, clk,
   output [(DATA_WIDTH-1):0] q
);

	// Declare the RAM Unit.
	reg [DATA_WIDTH - 1:0] ram[2**ADDR_WIDTH - 1:0];
	
	// Variable to hold the registered read address.
	reg [ADDR_WIDTH-1:0] addr_reg;
	
	// Use the contents of data.txt to initialize the data memory.
	initial begin
		$readmemh("data.txt", ram);
	end
	
	always@(posedge clk) begin
	// Write
		if(we)
			ram[addr] <= data;
		addr_reg  <= addr;
	end
	
	// Continuous assignment implies read returns NEW data.
	// This is the natural behavior of the TriMatrix memory blocks in Single Port mode.
	assign q = ram[addr];

endmodule
