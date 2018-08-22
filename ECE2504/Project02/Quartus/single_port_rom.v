// This file was created by 
// Tom Martin 
// 16 October 2012
// 
//  This module is the ROM for
//  design project 2
//  in ECE 2504 for Spring 2016. 
//  
// 
//  You must not modify any part of this file.

module single_port_rom
#(parameter DATA_WIDTH=8, parameter ADDR_WIDTH=4)
(
	input [(ADDR_WIDTH-1):0] addr,
	input clk,
	output reg [(DATA_WIDTH-1):0] q
);

	// Declare the ROM variable
	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];

	

	// Specify the ROM contents using the $readmemh command.
   // You must modify the contents of the rom.txt file to change the ROM contents.	
	initial 
	begin 
		$readmemh("rom.txt", rom);
	end 

	// Assign the output synchronously.
	always @ (posedge clk)
	begin
		q <= rom[addr];
	end

	
endmodule



