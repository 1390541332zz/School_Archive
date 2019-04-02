module fir(
	input 		          		CLOCK_50,
	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,
	input 		     [9:0]		SW
);

`define TAP 16

   reg [9:0] sysin, sysout, sysout_next;
	reg [9:0] tap[`TAP-1:0], tap_next[`TAP-1:0];
	reg [9:0] acc[`TAP-1:0];
   integer i;
	
	always @(posedge CLOCK_50)
	begin
	  sysout <= KEY[0] ? sysout_next : 10'b0;
	  for (i = 0; i < `TAP; i = i +1)
	    tap[i] <= KEY[0] ? tap_next[i] : 10'b0;
	end

	
	always @(*)
	begin
	
	  sysin = SW[9:0];

     tap_next[0] = sysin;	
	  for (i = 1; i < `TAP; i = i + 1)
	     tap_next[i] = tap[i-1];
		
     acc[0] = tap[0];
	  for (i = 1; i < `TAP; i = i + 1)
	     acc[i] = acc[i-1] + tap[i];
		
	  sysout_next = acc[15];
	end

	assign LEDR = sysout;

endmodule
