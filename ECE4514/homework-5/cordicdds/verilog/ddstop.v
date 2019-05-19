module ddstop(input wire clk,
	      input wire 	 reset,
	      input wire  [19:0] increment,
	      input wire 	 update,
	      output wire [15:0] q,
	      output wire 	 ready);

   wire [19:0] 			 angle, angle90;
   wire [19:0] 			 qw;
   wire 			 readyM1;
   wire [1:0] 			 quadrant;
   wire 			 readyM2;
   wire [19:0] 			 sine;
   wire 			 readyM3;
   wire [19:0] 			 incrementcast;
   
   accum  M1(.clk(clk), 
	     .reset(reset),
	     .update(update),
	     .increment(increment),
	     .angle(angle), 
	     .ready(readyM1));
   
   encoder M2(.clk(clk),
	     .reset(reset),
	     .update(readyM1),
	     .angle360(angle),
	     .angle90(angle90),
	     .quadrant(quadrant),
	     .ready(readyM2));

   cordic M3(.clk(clk),
	     .reset(reset),
	     .update(readyM2),
	     .angle(angle90),
	     .Yout(sine),
	     .ready(readyM3));

   assign qw    = (quadrant < 2'h2) ? sine : -sine;
   assign q     = qw[16:1];
   assign ready = readyM3;

endmodule
