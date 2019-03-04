module sinewave(
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
	input 		     [9:0]		SW,
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

	// THIS INSTANTIATES THE I2C MASTER 
	// REFER TO THE TONEGEN DESIGN TO FIND 
	// WHAT THIS MODULE SHOULD DO. YOU CAN
	// DIRECTLY COPY OVER THE RELEVANT VERILOG
	// FILES TO THIS DIRECTORY

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

	// THIS INSTANTIATES THE SINE WAVE GENERATOR
	// YOU HAVE TO CREATE THIS DESIGN BY
	//  1. STUDYING TONEGEN
	//  2. STUDYING CORDIC_DDS
	//
	// BASICALLY, THIS MODULE DOES THE SAME FUNCTION AS
	// THE AUDIOGEN MODULE IN TONEGEN. HOWEVER, INSTEAD
	// OF SAMPLES FROM A SQUARE WAVE, YOU HAVE TO FEED IT
	// SAMPLES FROM THE CORDIC DDSTOP MODULE

	sinegen AUDIO ( .clk(CLOCK_50),
				    .reset(reset),
	                .adcdat(AUD_ADCDAT),
	                .adclrck(AUD_ADCLRCK),
	                .bclk(AUD_BCLK),
	                .dacdat(AUD_DACDAT),
	                .daclrck(AUD_DACLRCK),
	                .sw(SW[9:0])
				  );

	assign GPIO[11] = AUD_ADCDAT;
	assign GPIO[13] = AUD_ADCLRCK;
	assign GPIO[15] = AUD_BCLK;
	assign GPIO[17] = AUD_DACDAT;
	assign GPIO[19] = AUD_DACLRCK;

endmodule

// quartus_sh --flow compile sinewave
// quartus_pgm -m jtag -o "p;sinewave.sof@2"

