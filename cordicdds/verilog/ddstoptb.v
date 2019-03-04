`timescale 1ns/1ps

module ddstoptb;

   reg         clk;
   reg         reset;   
   reg  [19:0] increment;
   reg         update;
   wire [15:0] q;
   wire        ready;

   reg [15:0]  increment_parameter;
   reg [31:0]  samples_parameter;   
   reg [15:0]  testvec [0:29999];
   integer     vecnum;
   integer     errors;

   initial 
     begin
	 $readmemh("vector.txt", testvec);
	 vecnum = 2;
	 errors = 0;
	 increment_parameter = testvec[1];
	 samples_parameter   = testvec[0];	
	 $display("--> Testing %d vectors for angle step %d", 
	 			samples_parameter, increment_parameter);
     end
   
   ddstop M1(.clk(clk),
	     .reset(reset),
	     .increment(increment),
	     .update(update),
	     .q(q),
	     .ready(ready));
   
   initial
     begin
	reset     = 1'b1;
	increment = increment_parameter; 
	#50;
	reset = 1'b0;
     end
   
   always
     begin
	clk = 1'b0;
	#10;
	clk = 1'b1;
	#10;
     end
   
   always
     begin	
	update = 1'b0;
	#100;
	update = 1'b1;
	#20;
	update = 1'b0;
	@(posedge ready);
	if (q !== testvec[vecnum])
	  begin
	     errors = errors + 1;
	     $display("**> Vector %5d: Received %4x Expected %4x", vecnum-2, q, testvec[vecnum]);
	  end
	vecnum = vecnum + 1;
	if ((vecnum - 2) == samples_parameter)
	  begin
	     $display("--> Simulation Complete. %d errors", errors); 
	     $stop;
	  end
     end
   
endmodule
	
	
