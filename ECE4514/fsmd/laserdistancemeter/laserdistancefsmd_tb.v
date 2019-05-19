`timescale 1ns/1ps

module laserdistancefsmd_tb;
   
   reg clk;
   reg reset;
   reg B;
   reg S;
   
   wire L;
   wire [15:0] D;
   
   laserdistancefsmd myfsmd(clk, reset, B, S, L, D);
   
   initial
     begin
	reset = 1'b1;
	clk   = 1'b0;
	S     = 1'b0;
	S     = 1'b0;
	#500
	  reset = 1'b0;
     end
   
   always #50 clk = ~clk;
   
   initial
     $monitor("t %8d reset %d B %d S %d L %d D %8d", $time, reset, B, S, L, D);	
	
   initial
     begin
	#1000  B = 1'b1;
	#75    B = 1'b0;
	
	#10025 S = 1'b1;
	#75    S = 1'b0;
	
	#525   B = 1'b1;
	#75    B = 1'b0;
	
	#30025 S = 1'b1;
	$stop;
     end
   
endmodule
