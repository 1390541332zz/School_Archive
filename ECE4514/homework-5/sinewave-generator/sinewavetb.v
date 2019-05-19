`timescale 1ns/1ns

module sinewavetb;

	reg  AUD_ADCDAT;
	wire AUD_ADCLRCK;
	reg  AUD_BCLKr;
	wire AUD_BCLK;
	wire AUD_DACDAT;
	reg  AUD_DACLRCKr;
	wire AUD_DACLRCK;
	wire AUD_XCK;

	reg CLOCK2_50;
	reg CLOCK3_50;
	reg CLOCK4_50;
	reg CLOCK_50;

	wire FPGA_I2C_SCLK;
	wire FPGA_I2C_SDAT;

	reg [3:0] KEY;
	wire [9:0] LEDR;
	wire [35:0] GPIO;
  reg [9:0] SW;

	sinewave DUT(AUD_ADCDAT,
	             AUD_ADCLRCK,
	             AUD_BCLK,
	             AUD_DACDAT,
	             AUD_DACLRCK,
	             AUD_XCK,
	             CLOCK2_50,
	             CLOCK3_50,
	             CLOCK4_50,
	             CLOCK_50,
	             FPGA_I2C_SCLK,
	             FPGA_I2C_SDAT,
               KEY,
               LEDR,
               SW,
               GPIO);

   wire [7:0] myReg0;
   wire [7:0] myReg1;
   wire [7:0] myReg2;
   wire [7:0] myReg3;
   wire [7:0] myReg4;
   wire [7:0] myReg5;
   wire [7:0] myReg6;
   wire [7:0] myReg7;
   
   i2cSlave receiver(.clk(CLOCK_50),
                     .rst(~KEY[0]),
                     .sda(FPGA_I2C_SDAT),
                     .scl(FPGA_I2C_SCLK),
                     .myReg0(myReg0),
                     .myReg1(myReg1),
                     .myReg2(myReg2),
                     .myReg3(myReg3),
                     .myReg4(myReg4),
                     .myReg5(myReg5),
                     .myReg6(myReg6),
                     .myReg7(myReg7)
                     );

   initial
     begin
        SW = 10'h3FF;
        KEY[0] = 1'b1;
        KEY[1] = 1'b1;
        KEY[2] = 1'b1;
        KEY[3] = 1'b1;
        #200;
        KEY[0] = 1'b0; // reset
        #200;
        KEY[0] = 1'b1;
     end
   
   always 
     begin
        CLOCK_50 = 1'b0;
        #10;
        CLOCK_50 = 1'b1;
        #10;
     end

   always 
     begin
        AUD_BCLKr = 1'b0;
        #160;
        AUD_BCLKr = 1'b1;
        #160;
     end

   always 
     begin
        AUD_DACLRCKr = 1'b0;
        #10240;
        AUD_DACLRCKr = 1'b1;
        #10240;
     end

    assign AUD_BCLK    = AUD_BCLKr;
    assign AUD_DACLRCK = AUD_DACLRCKr;

	initial
	  begin
	     	#10000;
	     	KEY[2] = 1'b0;
	     	#50;
	     	KEY[2] = 1'b1;
	  end
	  
endmodule
