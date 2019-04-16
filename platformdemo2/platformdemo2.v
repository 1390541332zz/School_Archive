module platformdemo2(
	input 		          		CLOCK_50,

	output		     [6:0]		HEX0,
	output		     [6:0]		HEX1,
	output		     [6:0]		HEX2,
	output		     [6:0]		HEX3,
	output		     [6:0]		HEX4,
	output		     [6:0]		HEX5,

	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,
	input 		     [9:0]		SW
);


        wire [7:0] led, switch;
        wire reset;

		  qsystop u0 (
                .clk_clk         (CLOCK_50),
                .ledout_export   (led),
                .reset_reset_n   (reset),
                .switchin_export (switch),
                .hex0_readdata   (HEX0),
                .hex1_name       (HEX1),
                .hex2_readdata   (HEX2),
                .hex3_readdata   (HEX3),
                .hex4_readdata   (HEX4),
                .hex5_readdata   (HEX5) 
        );


        assign LEDR[7:0] = led;
        assign switch    = SW[7:0];
        assign reset     = KEY[0];

        // quartus_sh --flow compile platformdemo2
        // quartus_pgm -m jtag -o "p;platformdemo2.sof@2"


endmodule
