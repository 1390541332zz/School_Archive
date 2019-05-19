module ro16(input wire        clk,
	    input wire [31:0] cmd,
	    output reg [31:0] r50,
	    output reg [31:0] osc);
   
   wire [0:15]		         ro_en;
   wire [0:15] 		      ro_q;
   wire                    ro_clk;
      
   always @ (posedge clk or negedge cmd[17]) begin
      if (~cmd[17])
	r50 <= 32'b0;
      else
	r50 <= cmd[16] ? (r50 + 32'b1) : r50;
   end
   
   rocell myro[0:15] (ro_en, ro_q);
   
   assign ro_en     = cmd[15:0];
   assign ro_clk    =^ ro_q;
   
   always @ (posedge ro_clk or negedge cmd[17]) begin
      if (~cmd[17])
	osc <= 32'b0;
      else
	osc <= (osc + 32'b1);
   end

endmodule	    