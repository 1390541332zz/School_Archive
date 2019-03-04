`include "constants.h"
   
module encoder( input wire clk,
		input wire 	   reset,
		input wire 	   update,
		input wire [19:0]  angle360,
		output wire [19:0] angle90,
		output wire [1:0]  quadrant,
		output wire 	   ready
		);

   wire signed [19:0] 			   angle1;
   
   assign angle1 = (angle360 > `PI4) ? angle360 - `PI4 : angle360;
   
   assign quadrant = (angle1 > `PI3) ? 2'h3 :
	             (angle1 > `PI2) ? 2'h2 :
	             (angle1 > `PI1) ? 2'h1 : 2'h0;
   
   assign angle90  = (angle1 > `PI3) ? (`PI4 - angle1) :
	             (angle1 > `PI2) ? (angle1 - `PI2)  :
	             (angle1 > `PI1) ? (`PI2 - angle1) : angle1;
   
   assign ready    = update;
   
endmodule
