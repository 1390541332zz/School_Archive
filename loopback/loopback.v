module loopback(
	input 		          		AUD_ADCDAT,
	inout 		          		AUD_ADCLRCK,
	inout 		          		AUD_BCLK,
	output		          		AUD_DACDAT,
	inout 		          		AUD_DACLRCK,
	output		          		AUD_XCK,

	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,

	output		          		FPGA_I2C_SCLK,
	inout 		          		FPGA_I2C_SDAT,

	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,

	inout 		    [35:0]		GPIO
);

	// ---- reset ----
	wire reset;
	assign reset = ~KEY[0];

	// ---- heartbeat ----
	reg [24:0] counter, counternext;

	always @(posedge CLOCK_50)
	counter <= (reset) ? 24'h0 : counternext;

	always @(*)
	counternext = counter + 24'h1;

	assign LEDR[9] = counter[24];

	//---------- YOUR DESIGN STARTS HERE -----------------
	// You can add code to this file, or add new verilog files.
	// If you add new files, put all of them in the same directory
	// as this file.




endmodule

// quartus_sh --flow compile loopback
// quartus_pgm -m jtag -o "p;loopback.sof@2"
