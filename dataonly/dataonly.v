
// pattern recognizer for pattern '001'
module dataonly(input wire clk,
				input wire rst,
				input wire data,
				output wire found);

	reg [2:0] state, nextstate;
	parameter S0 = 0, S1 = 1, S2 = 2, S3 = 3;

	always @(posedge clk)
	state <= (rst) ? 3'b0 : nextstate;

	always @(*)
	begin
		nextstate = state;
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
		  default: 
		      nextstate = S0;		  	  
		endcase
	end

    assign found = (state == S3) ? 1'b1 : 1'b0;

endmodule