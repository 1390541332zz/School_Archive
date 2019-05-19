
module qsystop (
	clk_clk,
	ledout_export,
	reset_reset_n,
	switchin_export,
	hex0_readdata,
	hex1_name,
	hex2_readdata,
	hex3_readdata,
	hex4_readdata,
	hex5_readdata);	

	input		clk_clk;
	output	[7:0]	ledout_export;
	input		reset_reset_n;
	input	[7:0]	switchin_export;
	output	[6:0]	hex0_readdata;
	output	[6:0]	hex1_name;
	output	[6:0]	hex2_readdata;
	output	[6:0]	hex3_readdata;
	output	[6:0]	hex4_readdata;
	output	[6:0]	hex5_readdata;
endmodule
