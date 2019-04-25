module nrdiv(Z, R, done, X, Y, start, clk);
   output [7:0] Z;
   output [15:0] R;
   output 	 done;
   input [15:0]  X;
   input [15:0]  Y;
   input 	 start;
   input 	 clk;
   
   reg [7:0] 	 Q;
   reg [15:0] 	 R;
   
   reg [5:0] 	 cnt;
   reg 		 done;
   reg 		 last;
   
   always @(posedge clk) begin
      done <= 0;
      last <= 0;
      if (start)
	cnt <= 0;
      else
	cnt <= cnt + 1;
      if (cnt == 6'd6) 
	last <= 1;
      else if (cnt == 6'd7) 
	done <= 1;
   end
   
   always @(posedge clk)
     if (start)
       R <= 2 * X - Y;
     else if (~last & R[15])
       R <= (R << 1) + Y;
     else if (~last)
       R <= (R << 1) - Y;
     else if (last & R[15])
       R <= R + Y;
     else
       R <= R;
   
   always @(posedge clk)
     if (start)
       Q <= 0;
     else if (~last)
       Q <= R[15] ? {Q[6:0], 1'b0} : 
            {Q[6:0], 1'b1};
     else if (last & R[15])
       Q <= {Q[6:0], 1'b0};
     else if (last & ~R[15])
       Q <= {Q[6:0], 1'b1};
     else
       Q <= Q;
   
   assign Z = Q;
   
endmodule
