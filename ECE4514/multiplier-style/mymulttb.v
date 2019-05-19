`timescale 1ns/1ps

module mymulttb;
   
   reg clk, reset;
   
   always
     begin
	clk = 1'b0;
	#25;
	clk = 1'b1;
	# 25;
     end
   
   initial
     begin
	reset = 1'b1;
	#50;
	reset = 1'b0;
     end
   
   reg [15:0]  a, b;
   wire [31:0] r;
   integer     n;
   reg 	       start;
   wire        done;
   
   mymult4 DUT(.clk(clk),
	       .reset(reset),
	       .a(a),
	       .b(b),
	       .start(start),
	       .result(r),
	       .done(done));
   
   integer     cycles, delta;
   initial cycles = 0;
   always @(posedge clk)
     cycles = cycles + 1;
   
   initial
     begin
	a     = 16'b0;
	b     = 16'b1;
	start = 1'b0;
	@(negedge reset);
	
	for (n=0; n < 1024; n = n + 1)
	  begin
	     start  = 1'b1;
	     delta  = cycles;
	     @(posedge done);
	     delta  = cycles - delta;
	     
 	     $display("C %d: a %x b %x m %x", delta, a, b, r);
	     
	     start = 1'b0;	     
	     @(negedge done);
	     
	     a = a + 16'd1;
	     b = {b[14:0], b[15]};
	  end
	
     end
   
endmodule
