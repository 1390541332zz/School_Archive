////////////////////////////////////////////////////////////////////////////////////////////////////
// File: cpu.v
//
// **************************************
// You MAY modify this file in Project 3.
// DO NOT MODIFY this file in Project 4.
// **************************************
//
// Description: This module specifies the top-level component for a single-cycle computer as shown
//              in Figure 8-15 on Page 460. It is mainly a structural module whose units are
//              implemented in other modules in this project.
//
// Modified by Tom Martin, 11/11/2012
//	Modified by P. Athanas, 03/2013
// Modified by KLC, 11/2013
// Modified by KLC, 11/2015
//
// - Removed accelerometers and EEPROM.
// - Added IR and PC outputs to make them visible.
// - Fixed warnings about the memory address input width.
// - Added r6 and r7
// - Added synthesis keep directives.
////////////////////////////////////////////////////////////////////////////////////////////////////

// You must not change the module declaration.

`timescale 1 ns/1 ps

module cpu(rst, clk, r0, r1, r2, r3, r4, r5, r6, r7, IR, PC);
	input rst;
	input clk;

	// The following outputs are included so that we can connect them to the LEDS
	// and see what is going on inside the CPU.

	output [15:0] r0, r1, r2, r3, r4, r5, r6, r7	/* synthesis keep */;
	output [15:0] IR, PC                         	/* synthesis keep */;

	wire [15:0] instr                 				/* synthesis keep */;
	wire [2:0]  DA, AA, BA             				/* synthesis keep */;
	wire        MB                 				    /* synthesis keep */;
	wire [3:0]  FS                     				/* synthesis keep */;
	wire        N, C, V, Z							/* synthesis keep */;
	wire        MD, RW, MW, PL, JB, BC				/* synthesis keep */;
	wire [15:0] constant;
	wire [15:0] register_file_in, A, B				/* synthesis keep */;

	wire [15:0] mux_b_out							/* synthesis keep */;
	wire [15:0] function_unit_out					/* synthesis keep */;
	wire [15:0] data_mem_out						/* synthesis keep */;
	wire [5:0]  ad;    								// Address offset.
	wire [15:0] se_ad;								// Sign-extended address offset.

	wire [15:0] data_in_bus							/* synthesis keep */;

// End module declaration.

	// The AD field, with sign extension.
	assign ad    = {instr[8:6], instr[2:0]};
	assign se_ad = {{10{ad[5]}}, ad};

	//Instantiate the PC controller.
	pc_controller pc_ctrl
	(
		.rst(rst),
		.clk(clk),
		.N(N),
		.C(C),
		.V(V),
		.Z(Z),
		.PL(PL),
		.JB(JB),
		.BC(BC),
		.PC(PC),
		.ld_pc(se_ad),
		.jp_addr(A)
	);

	// Instantiate the 1K x 16 instruction memory.
	// It uses only the lower 10 bits of PC since the memory is 1K.
	// These parameters control the size of the memory. Do not change them.

	defparam instr_mem.DATA_WIDTH = 16;
	defparam instr_mem.ADDR_WIDTH = 10;
	instruction_rom instr_mem(.addr(PC[9:0]), .clk(clk), .rst(rst), .q(instr));

	// Instantiate instruction decoder
	instr_decoder instruction_decoder
	(
		.instr(instr),
		.DA(DA),
		.AA(AA),
		.BA(BA),
		.MB(MB),
		.FS(FS),
		.MD(MD),
		.RW(RW),
		.MW(MW),
		.PL(PL),
		.JB(JB),
		.BC(BC)
	);

	// Instantiate the register file.
	dual_port_ram register_file
	(
		.data((register_file_in & (~rst))),
		.DA(DA),
		.AA(AA),
		.BA(BA),
		.we(RW),
		.clk(clk),
		.rst(rst),
		.a(A),
		.b(B),
		.r0(r0),
		.r1(r1),
		.r2(r2),
		.r3(r3),
		.r4(r4),
		.r5(r5),
	    .r6(r6),
	    .r7(r7)
	);

	// Zero fill the immediate operands to 16 bits.
	assign constant = {{13{1'b0}},instr[2:0]};

	// Instantiate multiplexer B.
	mux mux_b
	(
		.din_1(constant),
		.din_0(B),
		.sel(MB),
		.q(mux_b_out)
	);

	// Instantiate function unit.
	function_unit func_unit
	(
		.FS(FS),
		.A(A),
		.B(mux_b_out),
		.V(V),
		.C(C),
		.N(N),
		.Z(Z),
		.F(function_unit_out)
	);

	// Instantiate the data memory: 256 x 16 data memory.
	// These parameters control the size of the memory. Do not change them.

	defparam data_mem.DATA_WIDTH = 16;
	defparam data_mem.ADDR_WIDTH = 8;
	single_port_ram data_mem(.data(mux_b_out), .addr(A[7:0]), .we(MW), .clk(clk), .q(data_mem_out));

	// Take the data memory out as an input to multiplexer D.
	assign data_in_bus = data_mem_out;

	// Instatiate multiplexer D.
	mux mux_d
	(
		.din_1(data_in_bus),
		.din_0(function_unit_out),
		.sel(MD),
		.q(register_file_in)
	);

	// Make the instruction register value visible outside the CPU.
	assign IR = instr;

endmodule
// End of CPU module
