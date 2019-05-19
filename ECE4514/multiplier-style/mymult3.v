module mymult3(input  wire        clk,
	       input wire 	  reset,
	       input wire [15:0]  a,
               input wire [15:0]  b,
	       input wire 	  start,
	       output wire [31:0] result,
	       output wire 	  done);
   
   (* multstyle = "logic" *) reg [31:0] r, next_r;
   reg 				  d, next_d;
   
   always @(posedge clk)
     begin
	r <= (reset) ? 32'h0 : next_r;
	d <= (reset) ? 1'b0  : next_d;	
     end
   
   // IMPLEMENTATION 3
   reg [31:0] tmp, next_tmp;
   reg [31:0] tmpa, next_tmpa;
   reg [15:0] shftb, next_shftb;   
   
   reg [1:0]  state, next_state;
   localparam S0 = 0, S1 = 1, S2 = 2;
   
   always @(posedge clk)
     begin
	tmp   <= (reset) ? 32'b0 : next_tmp;
	tmpa  <= (reset) ? 32'b0 : next_tmpa;
	shftb <= (reset) ? 16'b0 : next_shftb;	
	state <= (reset) ? S0    : next_state;
     end
   
   always @(*)
     begin
	next_tmpa  = tmpa;
	next_shftb = shftb;
	next_tmp   = tmp;
	next_state = state;
	next_d     = 1'b0;
	next_r     = r;
	case(state)
	  S0: if (start)
	    begin
	       next_tmpa  = {16'b0, a};
	       next_shftb = b;
	       next_tmp   = 32'b0;
	       next_state = S1;
	    end
	  S1: if (|shftb)
	    begin
	       next_tmpa  = tmpa << 1;
	       next_shftb = shftb >> 1;
	       next_tmp   = tmp + (shftb[0] ? tmpa : 32'b0);
            end
	  else
	    next_state = S2;
	  S2: begin
	     next_d = 1'b1;
	     next_r = tmp;
	     next_state = S0;
	  end
	  default:
	    next_state = S0;
	endcase
     end
   
   assign result = r;
   assign done   = d;
   
endmodule
