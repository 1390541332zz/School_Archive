////////////////////////////////////////////////////////////////////////////////
// Modify this header with your name, date, etc.

// Filename: project5Top.v
// Author:   Jason Thweatt
// Date:     12 November 2015
// Revision: 1
// 
// Description: 
// This is the top level module for ECE 3544 Project 5.
// Do not modify the module declarations or ports in this file.
// Make a pin assignment before you program your board with this design!

module project5Top(CLOCK_50, KEY, SW, HEX5, HEX4, HEX3, HEX2, HEX1, HEX0, LED);
	input        CLOCK_50;
	input  [3:0] KEY;
	input  [9:0] SW;
	output [6:0] HEX5, HEX4, HEX3, HEX2, HEX1, HEX0;
	output [9:0] LED;
	
// Add your reg/wire/parameter declarations, module instantions, and so on.



// Delete the following assignments from here to the end of the module. 
// They are testing the switches, pushbuttons, displays, and LEDs.
	assign LED[9]   = SW[9] & SW[8];
	assign LED[8]   = SW[7] | SW[6];
	assign LED[7]   = ~(SW[5] ^ SW[4]);
	assign LED[6]   = ~(SW[3] | SW[2]);
	assign LED[5]   = SW[1];
	assign LED[4]   = ~SW[0];
	assign LED[3:0] = KEY[3:0];

	assign HEX5 = 7'h7f;
	assign HEX4 = 7'h7f;
	assign HEX3 = 7'h7f;
	assign HEX2 = 7'h7f;
	assign HEX1 = 7'h7f;
	assign HEX0 = SW[6:0];

endmodule
