`include "constants.h"

module cordic(input  wire clk,
              input  wire reset,
              input  wire update,
              input  wire [19:0] angle,
              output wire [19:0] Yout,
	      output wire ready);
   
   wire [ 3:0] 		  iter;
   wire [19:0] 		  lutval;
   
   cordicconst TABLE(.clk(clk),
		     .reset(reset),
		     .address(iter),
		     .data(lutval)
		     );
   
   localparam S0 = 0, S1 = 1, S2 = 2;
   
   reg [3:0] 		  	state, statenext;
   reg [3:0] 		  	ctr, ctrnext;
   reg signed [19:0] 	X, Xnext;  // X (cosine)
   reg signed [19:0] 	Y, Ynext;  // Y (sine)
   reg signed [19:0] 	A, Anext;  // accumulator angle
   reg signed [19:0] 	T, Tnext;  // target angle
   
   reg 			  		done, donenext;
   reg [19:0] 		  	result, resultnext;

   reg signed [19:0] 	Xshift, Yshift;
      
   always @(posedge clk)
     if (reset) begin
	ctr    <= 4'h0;
	state  <= S0;
	X      <= 20'h0;
	Y      <= 20'h0;
	A      <= 20'h0;
	T      <= 20'h0;
	done   <= 1'b0;
	result <= 20'h0;
     end else begin 
	ctr    <= ctrnext;
	state  <= statenext;
	X      <= Xnext;
	Y      <= Ynext;
	A      <= Anext;
	T      <= Tnext;	
	done   <= donenext;
	result <= resultnext;
     end
   
   assign iter = ctr; // drives lookup table address
   
   always @(*)
     begin
    	ctrnext   = ctr;
    	statenext = state;
    	case (state)
    	  S0:
	    begin
    	       ctrnext = 4'h0;
    	       if (update == 1'b1)
		 statenext = S1;
	    end
    	  S1:
	    begin
    	       ctrnext = ctrnext + 4'b1;
	       if (ctr == 4'hf)
		 statenext = S2;
	    end
	  S2:
	    statenext = S0;
	  default:
	    statenext = S0;
	endcase
     end

   always @(*)
     begin
       	Xnext      = X;
    	Ynext      = Y;
    	Anext      = A;
	Tnext      = T;
	donenext   = 1'b0;
	resultnext = result;
	Xshift     = 20'b0;
	Yshift     = 20'b0;       
	case (state)
	  S0:
	    begin
	       Xnext = `AG;
	       Ynext = 20'h0;
	       Anext = 20'h0;
	       Tnext = angle;
	    end
	  S1:
	    begin
	       Xshift = (X >>> ctr);
	       Yshift = (Y >>> ctr);
	       Anext  = (T > A) ?  A + lutval  : A - lutval;
	       Xnext  = (T > A) ?  X - Yshift  : X + Yshift;
	       Ynext  = (T > A) ?  Xshift + Y  : Y - Xshift;
	    end
	  S2:
	    begin
	       resultnext = Y;
	       donenext   = 1'b1;
	    end
	endcase // case (state)
     end

   assign ready = done;
   assign Yout = result;

endmodule
