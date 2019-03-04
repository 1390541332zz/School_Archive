`include "constants.h"

module accum(input clk,
	     input 		reset,
	     input wire 	update,
	     input wire [19:0] 	increment,
	     output wire [19:0] angle,
	     output wire        ready);

   reg signed [19:0] 			acc, accnext;
   reg 				done, donenext;
   reg signed [19:0]                   accchk;
   
   always @(posedge clk)
     begin
	acc  <= (reset) ? 20'b0 : accnext;
	done <= (reset) ? 1'b0 : donenext;
     end

   always @(*)
     begin
	donenext = 0;	
	accnext = acc;
	if (update)
	  begin
	     accchk = acc + increment;	     
	     accnext = (accchk > `PI4) ? accchk - `PI4 : accchk;
	     donenext = 1;
	  end
     end
   
   assign angle = acc;
   assign ready = done;
   
endmodule
