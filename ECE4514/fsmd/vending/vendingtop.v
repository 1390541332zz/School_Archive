module vendingtop(
		  input        clock,
		  input [3:0]  key,
		  output [9:0] led);

   vendingfsmd dut(clock, 
		   key[0], 
		   key[1], 
		   led[0]);

endmodule
