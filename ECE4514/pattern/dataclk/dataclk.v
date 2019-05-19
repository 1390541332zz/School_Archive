
// pattern recognizer for pattern '001'
module dataclk (input wire clk,
				input wire rst,
				input wire data,
				input wire dataclk,
				output wire found);

	reg  olddataclk;
	wire nextolddataclk;
	wire dataclkedge;

	reg  [2:0] state, nextstate;
	parameter S0 = 0, S1 = 1, S2 = 2, S3 = 3;

	always @(posedge clk)
	begin
	olddataclk <= (rst) ? 1'b0 : nextolddataclk;
	state      <= (rst) ? 3'b0 : nextstate;
	end

	assign dataclkedge    = dataclk & ~olddataclk;
	assign nextolddataclk = dataclk;

	always @(*)
	begin
		nextstate      = state;
		if (dataclkedge) begin
		  case (state)
		    S0: if (data == 1'b0)
		    	  nextstate = S1;
		    S1: if (data == 1'b0)
		    	  nextstate = S2;
		    	else 
		    	  nextstate = S0;
		    S2: if (data == 1'b1)
		          nextstate = S3;
		    S3: if (data == 1'b0)
		          nextstate = S1;
		        else
		          nextstate = S0;
		  default: nextstate = S0;		  	  
		endcase
		end
	end

    assign found = (state == S3) ? 1'b1 : 1'b0;

endmodule