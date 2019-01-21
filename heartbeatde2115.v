module heartbeatde2115(
	input 		          		CLOCK_50,
	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,

	output		     [8:0]		LEDG,
	output		    [17:0]		LEDR,

	input 		     [3:0]		KEY
);

reg [17:0] ledr_reg;
reg [23:0] count_reg;

wire       tick;

always @(posedge CLOCK_50)
  if (KEY[0] == 1'b0)
    begin
      ledr_reg  <= 18'b1;
      count_reg <= 24'd0;
    end
  else
    begin
      ledr_reg  <= tick ? {ledr_reg[16:0], ledr_reg[17]} : ledr_reg;
      count_reg <= tick ? 24'd0 : count_reg + 24'd1;
  end

assign tick = (count_reg == 24'd5000000);
assign LEDR = ledr_reg;
assign LEDG = 9'd0;

endmodule

// quartus_sh --flow compile heartbeat
// quartus_pgm -m jtag -o "p;heartbeat.sof@1"

