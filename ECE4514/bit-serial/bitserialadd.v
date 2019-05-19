module bitserialadd(input  clk,
                    input  reset,
                    input  a,
                    input  b,
                    output q);

  // symbolic state assignment
  // ie. the numbers are used for RTL simulation purposes
  // but the actual synthesis result may use something different
  localparam S0 = 0, S1 = 1, S2 = 2, S3 = 3;    

   // state register
   // syn_encoding a synthesis attribute. 
   // It specifies the state encoding to be used for synthesis
  (* syn_encoding = "default" *) reg [1:0] state, statenext;

  // register
  always @(posedge clk)
   begin
    if (reset)       // synchronous reset
      state <= S0;   // initial state
    else
      state <= statenext;
   end

   

  // next-state logic
  always @(*)
   begin
   statenext = state;  // always add a default assignment
   case (state)
     S0,S1: begin
     	    if (a & b)
     	      statenext = S2;
     	    else if (a | b)
     	      statenext = S1;
     	    else 
     	      statenext = S0;
         end
     S2,S3: begin
     	    if (a & b)
     	      statenext = S3;
     	    else if (a | b)
     	      statenext = S2;
     	    else 
     	      statenext = S1;
            end
     default:         // always add a default (safe) case
            statenext = S0;
     endcase
   end
      
   // output function
   assign q = ((state == S1) || (state == S3)) ? 1'b1 : 1'b0;

endmodule