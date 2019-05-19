module top(
	input clock,
	input [3:0] key,
	output [9:0] led);

   bitserialadd dut(clock, key[0], key[1], key[2], led[0]);

endmodule
