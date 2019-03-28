module timing(
	input 		          		CLOCK_50,
	output		     [8:0]		LEDG,
	input 		     [3:0]		KEY
);

	reg [99:0] count, count_next;
	
	always @(posedge CLOCK_50)
		count <= KEY[0] ? count_next : 100'hFFFFFFFFFFFFFFFFFFFFFFF0;
	
	always @(*)
		count_next = count + 100'b1;
		
	assign LEDG[8:0] = count[99:91];

endmodule
