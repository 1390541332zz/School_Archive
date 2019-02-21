module tonegen(
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
	inout 		    [35:0]		GPIO,
	input 		     [9:0]		SW
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

	// ---- audio clock ----
	reg [1:0] audioclock, audioclocknext;

	always @(posedge CLOCK_50)
	audioclock <= (reset) ? 2'h0 : audioclocknext;

	always @(*)
	audioclocknext = audioclock + 2'h1;

	assign AUD_XCK = audioclock[1];


	// ---- i2c interface ----
	wire loopback;
	wire audioon;
	wire audiooff;

	assign loopback = ~KEY[1];
	assign audioon  = ~KEY[2];
	assign audiooff = ~KEY[3];

	i2cmasterwrite I2C( .clk(CLOCK_50),
						.reset(reset),
						.loopback(loopback),
						.audioon(audioon),
						.audiooff(audiooff),
					    .sck(FPGA_I2C_SCLK),
					    .sda(FPGA_I2C_SDAT)
					  );
	
	assign GPIO[1] = FPGA_I2C_SCLK;
	assign GPIO[3] = FPGA_I2C_SDAT;

	// ---- tone generator ---

	audiogen AUDIO( .clk(CLOCK_50),
				    .reset(reset),
	                .adcdat(AUD_ADCDAT),
	                .adclrck(AUD_ADCLRCK),
	                .bclk(AUD_BCLK),
	                .dacdat(AUD_DACDAT),
	                .daclrck(AUD_DACLRCK),
	                .swhi(SW[3:0]),
	                .swlo(SW[7:4]) 
				  );

	assign GPIO[11] = AUD_ADCDAT;
	assign GPIO[13] = AUD_ADCLRCK;
	assign GPIO[15] = AUD_BCLK;
	assign GPIO[17] = AUD_DACDAT;
	assign GPIO[19] = AUD_DACLRCK;

endmodule

// quartus_sh --flow compile tonegen
// quartus_pgm -m jtag -o "p;tonegen.sof@2"
