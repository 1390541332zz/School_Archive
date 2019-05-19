module chipbiometrics(
	input 		          		CLOCK_50,
	output		     [6:0]		HEX0,
	output		     [6:0]		HEX1,
	output		     [6:0]		HEX2,
	output		     [6:0]		HEX3,
	output		     [6:0]		HEX4,
	output		     [6:0]		HEX5,
	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR
);

	bioqsys u0 (
		.clk_clk       (CLOCK_50),      
		.hex0_readdata (HEX0),
		.hex1_name     (HEX1),     
		.hex2_readdata (HEX2),
		.hex3_readdata (HEX3),
		.hex4_readdata (HEX4), 
		.hex5_readdata (HEX5) 
	);


endmodule

 // quartus_sh --flow compile chipbiometrics
 // quartus_pgm -m jtag -o "p;chipbiometrics.sof@2"

