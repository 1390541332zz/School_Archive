////////////////////////////////////////////////////////////////////////////////////////////////////
// File: instruction_rom.v
//
// ******************************************
// YOU ARE NOT PERMITTED TO MODIFY THIS FILE.
// ******************************************
//
// Description: This is a model of the Simple Computer's Instruction Memory. To meet the
//              single-cycle requirement, this ROM must have a single-cycle read address.
//
// Created: 06/2012, Xin Xin, Virginia Tech
////////////////////////////////////////////////////////////////////////////////////////////////////

module instruction_rom #(parameter DATA_WIDTH=8, parameter ADDR_WIDTH=6)
(
	input [(ADDR_WIDTH-1):0] addr,
	input clk,
	input rst,
	output  [(DATA_WIDTH-1):0] q
);

	// Declare the ROM Unit.
	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];

	// Use the contents of instruction.txt to initialize the instruction memory.
	initial begin
		$readmemh("instruction.txt", rom);
	end

	// Make this component purely combinational in order to meet "one clock cycle CPU" requirement
	assign q = (rst == 1'b1) ? 16'h0000 : rom[addr];

endmodule
