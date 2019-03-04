module audiogen(input  wire clk,
				input  wire reset,
				input  wire adcdat,
				input  wire adclrck,
				input  wire bclk,
				output wire dacdat,
				input  wire daclrck,
				input  wire [3:0] swhi,
				input  wire [3:0] swlo);

	reg [63:0] sample, samplenext;
    reg  oldbclk;
    wire oldbclknext;
    reg  oldlrck;
    wire oldlrcknext;
    wire bclktick;
    wire firstsample;

	always @(posedge clk)
	begin
		sample  = (reset) ? 64'h0 : samplenext;
		oldbclk = (reset) ?  1'h0 : oldbclknext;
		oldlrck = (reset) ?  1'h0 : oldlrcknext;
	end
	assign bclktick    = ( oldbclk & ~bclk);    // negative edge of bclk
	assign firstsample = (~oldlrck & daclrck);  // positive edge of lrck

	assign oldbclknext = bclk;
	assign oldlrcknext = daclrck;

	// --- tone generation logic ---

	reg [7:0] halfperiod, halfperiodnext;
	always @(posedge clk)
	begin
		halfperiod = (reset) ? 8'h0 : halfperiodnext;
	end
	always @(*) 
	begin
	halfperiodnext = halfperiod;
	if (firstsample)
			halfperiodnext = halfperiod + 8'h1;
	if (halfperiodnext == 8'd48)
			halfperiodnext = 8'd0;
	end

	wire [63:0] samplevalue;
	assign samplevalue = (halfperiod < 8'd24) ? 
						 {swhi, 28'h000_0000, swhi, 28'h000_0000} : 
						 {swlo, 28'h000_0000, swlo, 28'h000_0000};

	// --- DAC data shifting logic ---	
	always @(*)
	begin
		samplenext = (firstsample) ? samplevalue :
		             (bclktick)    ? {sample[62:0], 1'b0} : sample;
	end

	assign dacdat = sample[63];

endmodule
