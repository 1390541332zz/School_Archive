module laserdistancetop(
			 input 	      clock,
			 input [3:0]  key,
			 output [9:0] led);

   wire [15:0] D;
   
   laserdistancefsmd(.clk(clock),
		     .reset(key[0]),
		     .B(key[1]),
		     .S(key[2]),
		     .L(key[3]),
		     .D(D));
   
   assign led = D[15:6];
   
endmodule
