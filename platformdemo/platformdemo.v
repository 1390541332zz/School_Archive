module platformdemo(
	input 		          		CLOCK_50,
	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,
	input 		     [9:0]		SW
);

	wire [7:0] led, switch;
	wire reset;
	
	qsystop u0 (
		.clk_clk         (CLOCK_50),
		.reset_reset_n   (reset),
		.ledout_export   (led),
		.switchin_export (switch)
	);

	assign LEDR[7:0] = led;
	assign switch    = SW[7:0];
	assign reset     = KEY[0];

	// quartus_sh --flow compile platformdemo
   // quartus_pgm -m jtag -o "p;platformdemo.sof@2"
	
endmodule
