module expressions(
	input 		          		CLOCK_50,
	input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,
	inout 		    [35:0]		GPIO
);

	wire reset;
	wire clk;
	wire [3:0] mode;
	wire [7:0] a, b;
	reg  [7:0] c, cnext;
		
	assign reset = ~KEY[0];
	assign clk   = CLOCK_50;
	assign mode  = GPIO[35:32]; // arbitrary assignment
	assign a     = GPIO[ 7:0];  // arbitrary assignment
	assign b     = GPIO[15:8];  // arbitrary assignment

	always @(posedge clk)
	  c <= (reset) ? 16'b0 : cnext;

   integer n;
	
	always @(*)
		begin
		cnext = 8'b0;
		case (mode)
		
				// addition
		4'd0: cnext = a + b;
		
				// unsigned comparison
		4'd1: cnext = (a === b);

				// signed comparison
		4'd2: cnext = ($signed(a) > $signed(b));

            // integer division (not smart)
		4'd3: cnext = a / b;
		
            // data multiplication		
		4'd4: cnext = a * b;
		
				// constant multiplication
		4'd5: cnext = a * 5'd11;

			   // constant shift
		4'd6: cnext = a << 8'd2;
		
		      // data shift
		4'd7: cnext = a << b[2:0];

		      // priority mux
		4'd8: if (a == 8'd0) cnext = b;
		      else if (a == 8'd1) cnext = ~b;
				else if (a == 8'd2) cnext = |b;
				else cnext = ^b;

			   // multiplexer
		4'd9: cnext = (a < b) ? 8'd5 : 8'd23;
		
		       // for loop illustrating shift register
		4'd10: for (n = 7; n>0; n=n-1)
		           cnext[n] = c[n-1];
		
		       // two parallel adders
		4'd11: cnext = {a[7:4] + b[7:4], a[3:0] + b[3:0]};
		
		       // updown counter, two adders
		4'd12: cnext = a[0] ? c + 8'd1 : c - 8'd1;
					  
		       // updown counter, one adders
		4'd13: cnext = c + (a[0] ? 8'd1 : - 8'd1);
		
		       // constant modulo
		4'd14: cnext = a % 8'd139;

		      // arithmetic shift w sign extension
		4'd15: cnext = $signed(a) >>> 3'd5;

		default: cnext = c;
		endcase		
	end
	
	assign LEDR = c;
	
endmodule
