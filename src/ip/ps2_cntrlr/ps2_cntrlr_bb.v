
module ps2_cntrlr (
	ps2_0_reset,
	ps2_0_PS2_CLK,
	ps2_0_PS2_DAT,
	ps2_0_command,
	ps2_0_command_valid,
	ps2_0_command_ready,
	ps2_0_data_ready,
	ps2_0_data,
	ps2_0_data_valid,
	clk_clk,
	reset_reset_n);	

	input		ps2_0_reset;
	inout		ps2_0_PS2_CLK;
	inout		ps2_0_PS2_DAT;
	input	[7:0]	ps2_0_command;
	input		ps2_0_command_valid;
	output		ps2_0_command_ready;
	input		ps2_0_data_ready;
	output	[7:0]	ps2_0_data;
	output		ps2_0_data_valid;
	input		clk_clk;
	input		reset_reset_n;
endmodule
