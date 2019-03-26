module memory(
	input 		          		CLOCK_50,
	output		     [9:0]		LEDR,
	input 		     [9:0]		SW
);

  wire clk;
  wire en;
  wire we;
  wire [5:0] addr;
  wire [15:0] di;
  wire [15:0] do;

  my_ram R (clk, en, we, addr, di, do);

  assign clk  = CLOCK_50;
  assign en   = SW[0];
  assign we   = SW[1];
  assign addr = SW[9:0];
  assign di   = SW[9:2];
  assign LEDR = do[9:0];
  
endmodule
