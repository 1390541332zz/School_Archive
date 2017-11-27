////////////////////////////////////////////////////////////////////////////////////////////////////
// File: instr_decoder.v
//
// **************************************
// You MAY modify this file in Project 3.
// DO NOT MODIFY this file in Project 4.
// **************************************
//
// Description: This module corresponds to the Simple Computer's Instruction Decoder, as shown in
//              Figure 8-16 on Page 462.
//
// Created: 06/2012, Xin Xin, Virginia Tech
// Modified by JST, 10 April 2016 - Removed intermediate values
////////////////////////////////////////////////////////////////////////////////////////////////////

module instr_decoder
(
	input [15:0] instr,
	output [2:0] DA, AA, BA,
	output MB,
	output [3:0] FS,
	output MD, RW, MW, PL, JB, BC
);

	assign DA = instr[8:6];
	assign AA = instr[5:3];
	assign BA = instr[2:0];
	assign MB = instr[15];
	assign FS = {instr[12:10], (instr[9] & (~PL))};
	assign MD = instr[13];
	assign RW = ~instr[14];
	assign MW = ~instr[15] & instr[14];
	assign PL = instr[15] & instr[14];
	assign JB = instr[13];
	assign BC = instr[9];

endmodule
// End of instr_decoder module
