`timescale 1 ns/ 1ps

module timingtb;

   reg clk;
   reg  [3:0] key;
   wire [9:0] ledr;

   timing dut(.CLOCK_50(clk),
	      .KEY(key),
	      .LEDG(ledg));

   initial
     begin
	key = 3'b111;
	#100 key[0] = 1'b0;
	#100 key[0] = 1'b1;	
     end

   always
     begin
	clk = 1'b0;
	#20 ;
	clk = 1'b1;
	#20 ;	
     end

endmodule
