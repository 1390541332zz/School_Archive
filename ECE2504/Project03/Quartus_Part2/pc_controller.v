////////////////////////////////////////////////////////////////////////////////////////////////////
// File: pc_controller.v
//
// **************************************
// You MAY modify this file in Project 3.
// DO NOT MODIFY this file in Project 4.
// **************************************
//
// Description: This is a model of the Program Counter controller for the Simple Computer.
//
//              The Program Counter's next value depends on the kind of instruction being executed.
//              - The Jump instruction uses an address value from the instruction's target register
//                as its destination.
//              - The Branch instructions use an address offset contained in the instruction code,
//                and are also dependent in part upon status flags N and Z.
//              - All other instructions cause PC to advance to the next consecutive instruction.
//
// Created: 06/2012, Xin Xin, Virginia Tech
// Modified by KLC, Nov 2015 to fix R6/R7 LED viewing
////////////////////////////////////////////////////////////////////////////////////////////////////

`timescale 1 ns/1 ps

module pc_controller(rst, clk, N, C, V, Z, PL, JB, BC, PC, ld_pc, jp_addr, ret_pc);
	input             rst;
	input             clk;
	input             N, Z, V, C, PL, JB, BC;
	input [15:0]      ld_pc, jp_addr;
	output reg [15:0] PC;
    output [15:0]     ret_pc;
	wire [3:0]        status;
	wire [3:0]        ctrl_pc;
	reg  [15:0]       next_pc;

	assign ctrl_pc = {rst, PL, JB, BC};  // Concatenate the PC control bits
    assign ret_pc = PC + 1;

    always@(posedge clk) begin
		if(rst)
			PC <= 16'h0000;
		else
			PC <= next_pc;
	end

	// Logic to decide what is the next PC value based upon the 4 control bits, {rst, PL, JB, BC}

	always@(ctrl_pc or jp_addr or N or Z or PC or ld_pc) begin
		casex(ctrl_pc)
			4'b1xxx: next_pc = 16'h0000;  // PC = 0 on reset.
            4'b011x: next_pc = jp_addr;   // For the JUMP instruction, PC = jp_addr.
            4'b0011: next_pc = jp_addr;   // For the JAL instruction, PC = jp_addr. ret_pc = PC + 1
			4'b0101: begin				  // For Branch instructions, look at the status bits.
				if(N)
					next_pc = PC + ld_pc; // For Branch on Negative, PC = (PC + offset) if N = 1.
				else
					next_pc = PC + 16'b1; // Otherwise, PC = PC + 1.
				end
			4'b0100: begin
				if(Z)
					next_pc = PC + ld_pc; // For Branch on Zero, PC = (PC + offset) if Z = 1.
				else
					next_pc = PC + 1'b1;  // Otherwise, PC = PC + 1.
				end
			default: next_pc = PC + 1'b1; // For all other instructions, PC = PC + 1.
		endcase
	end

endmodule
