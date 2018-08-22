////////////////////////////////////////////////////////////////////////////////////////////////////
// File: mux.v
//
// ******************************************
// YOU ARE NOT PERMITTED TO MODIFY THIS FILE.
// ******************************************
//
// Description: This model implements a 16-bit wide two-to-one multiplexer.
//
// Created: 11/2012, Xin Xin, Virginia Tech
////////////////////////////////////////////////////////////////////////////////////////////////////

module mux
(
	input [15:0] din_1,
	input [15:0] din_0,
	input sel,
	output [15:0] q
);

	assign q = sel ? din_1 : din_0;

endmodule
