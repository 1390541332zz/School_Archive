module keyboard(
	input 		          		CLOCK_50,
	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR
);


	simplesys u0 (
		.clk_clk       (CLOCK_50),
		.reset_reset_n (KEY[0]),
		.led_export     (LEDR[7:0])
	);

   reg [23:0] 					heartbeat;

   always @(posedge CLOCK_50, negedge KEY[0])
     if (KEY[0] == 1'b0)
       heartbeat <= 24'b0;
     else
       heartbeat <= heartbeat + 1'b1;

   assign LEDR[9] = heartbeat[23];


endmodule
