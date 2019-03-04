module cordicconst(input wire         clk,
		   input wire 	      reset,
		   input wire [3:0]   address,
		   output wire [19:0] data);

   reg [19:0] 			      q;
   
   always @(*)
     begin
	q = 18'h0;
	case (address)
	  4'h0: q = 20'h6487;
	  4'h1: q = 20'h3b58;
	  4'h2: q = 20'h1f5b;
	  4'h3: q = 20'hfea;
	  4'h4: q = 20'h7fd;
	  4'h5: q = 20'h3ff;
	  4'h6: q = 20'h1ff;
	  4'h7: q = 20'hff;
	  4'h8: q = 20'h7f;
	  4'h9: q = 20'h3f;
	  4'ha: q = 20'h1f;
	  4'hb: q = 20'hf;
	  4'hc: q = 20'h7;
	  4'hd: q = 20'h3;
	  4'he: q = 20'h1;
	  4'hf: q = 20'h0;
	  default: q = 20'h0;
	endcase
     end // always @ (*)

   assign data = q;
   
endmodule
