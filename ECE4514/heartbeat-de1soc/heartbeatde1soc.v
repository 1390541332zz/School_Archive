module heartbeatde1soc(
	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,
	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR

  );

reg [9:0] ledr_reg;
reg [23:0] count_reg;

wire       tick ;

always @(posedge CLOCK_50)
  if (KEY[0] == 1'b0)
    begin
    ledr_reg <= 10'b1;
    count_reg <= 24'd0;
    end
  else
    begin
    count_reg <= tick ? 24'd0 : count_reg + 24'd1;
    ledr_reg  <= tick ? {ledr_reg[8:0], ledr_reg[9]} : ledr_reg;
  end

assign tick = (count_reg == 24'd5000000);
assign LEDR = ledr_reg;

endmodule

// quartus_sh --flow compile heartbeatde1soc
// quartus_pgm -m jtag -o "p;heartbeatde1soc.sof@2"
