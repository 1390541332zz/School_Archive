
module qsystop (
	clk_clk,
	reset_reset_n,
	ledout_export,
	switchin_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	ledout_export;
	input	[7:0]	switchin_export;
endmodule
