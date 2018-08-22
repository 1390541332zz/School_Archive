////////////////////////////////////////////////////////////////////////////////////////////////////
// File: function_unit.v
//
// **************************************
// You MAY modify this file in Project 3.
// DO NOT MODIFY this file in Project 4.
// **************************************
//
// Description: This module implements the function unit for the Simple Computer from Chapter 8.
//              It generates status flags for Overflow, Carry-out, Negative, and Zero: {V, C, N, Z}.
//              The Simple Computer uses N and Z in the Instruction Decoder.
//
// Created: 06/2012, Xin Xin, Virginia Tech
// Modified by P. Athanas, 3/2013
//   --> transformed into a structural model
// Modified by JST, 6/2013
//   --> Overflow flag fixed (was a carry-out)
// Modified by JST, 6/2015
//   --> Reformulated to match structure of the function unit described in the text.
////////////////////////////////////////////////////////////////////////////////////////////////////

module function_unit(FS, A, B, V, C, N, Z, F);

    input [3:0]   FS;			// Function Unit select code.
    input [15:0]  A, B;			// Function Unit operands A and B.
    output        V, C, N, Z;	// Function Unit status bits
    output [15:0] F;			// Function Unit result.

	// This is the select line for the Function Unit's output multiplexer.
	wire          MF;

	// These 17-bit vectors are zero-extended versions of the adder operands.
	wire [16:0]   arith_A, arith_B, arith_Cin;

	// These 17-bit vectors are results that include a carry-out.
	wire [16:0]   arith_out, logic_out, shift_out;
	wire [16:0]   temp_G, temp_F;

	// The arithmetic circuit uses FS[2:1] to pick (B, ~B, 0, -1) and makes FS[0] the carry-in.
	// The adder operands are zero-filled to 17 bits to generate a carry-out.
    assign arith_A   = {1'b0, A};
    assign arith_B   = (FS[2:1] == 2'b00) ? 17'b0      :
                       (FS[2:1] == 2'b01) ? {1'b0, B}  :
                       (FS[2:1] == 2'b10) ? {1'b0, ~B} :
                       (FS[2:1] == 2'b11) ? 17'hFFFF   : 17'bxxxxxxxxxxxxxxxxx;
	assign arith_Cin = {16'b0, FS[0]};
	assign arith_out = arith_A + arith_B + arith_Cin;

	// The logic circuit uses FS[1:0] to perform (AND, OR, XOR, Complement).
	assign logic_out = (FS[1:0] == 2'b00) ? {1'b0, A} & {1'b0, B} :
	                   (FS[1:0] == 2'b01) ? {1'b0, A} | {1'b0, B} :
                       (FS[1:0] == 2'b10) ? {1'b0, A} ^ {1'b0, B} :
                       (FS[1:0] == 2'b11) ? {1'b0, ~A}            : 17'bxxxxxxxxxxxxxxxxx;

	// The ALU uses FS[3] to perform (Arithmetic_Result, Logic_Result).
	assign temp_G    = (FS[3] == 1'b0) ? arith_out : logic_out;

	// The Shifter uses FS[1:0] to perform (B, sr B, sl B).
	assign shift_out = (FS[1:0] == 2'b00) ? {1'b0, B} :
	                   (FS[1:0] == 2'b01) ? {1'b0, 1'b0, B[15:1]} :
					   (FS[1:0] == 2'b10) ? {1'b0, B[14:0], 1'b0} : 17'bxxxxxxxxxxxxxxxxx;

	// The mux that chooses between the ALU and shifter has a select equal to (FS[3] & FS[2]).
	assign MF = FS[3] & FS[2];

	// The mux on the Function Unit output uses MF to perform (ALU, Shifter).
	assign temp_F = (MF == 1'b0) ? temp_G : shift_out;

	// Truncate temp_F to derive F.
	assign F = temp_F[15:0];

	// The overflow bit is not used in the Simple Computer.
	// It is defined here for completeness in terms of A, B, and F.
	// This V is only valid when FS[3] = 0, which is true only for arithmetic instructions.
   assign V = ~FS[3] & ((A[15] & B[15] & ~F[15]) | (~A[15] & ~ B[15] & F[15]));

	// The carry-out bit is not used in the Simple Computer.
	// It is defined here for completeness in terms of temp_F and FS.
	// This C is only valid when FS[3] = 0, which is true only for arithmetic instructions.
   assign C = ~FS[3] & temp_F[16];

	// The negative bit is used in the Simple Computer as the condition for Branch on Negative.
	// N is valid for non-shift operations. For shift operations, N = 0.
   assign N = (FS[3:2] != 4'b11) & F[15];

	// The zero bit is used in the Simple Computer as the condition for Branch on Zero.
	// Z is valid for non-shift operations. For shift operations, Z = 0.
   assign Z = (FS[3:2] != 4'b11) & (F == 16'h0000);

endmodule
