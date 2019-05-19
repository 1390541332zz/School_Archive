module mymult1(input  wire        clk,
	       input wire 	  reset,
	       input wire [15:0]  a,
               input wire [15:0]  b,
	       input wire 	  start,
	       output wire [31:0] result,
	       output wire 	  done);
   
   (* multstyle = "logic" *) reg [31:0] r, next_r;
   reg 				  d, next_d;
   
   always @(posedge clk)
     begin
	r <= (reset) ? 32'h0 : next_r;
	d <= (reset) ? 1'd0  : next_d;	
     end
   
   // IMPLEMENTATION 1
   always @(*)
     begin
	next_r = {16'b0,a} * {16'b0,b};
	next_d = start;	
     end
   
   assign done   = d;
   assign result = r;
   
endmodule
